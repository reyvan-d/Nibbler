//
// Created by Andromaleus on 2017-06-08.
//
//

#include "../includes/nibbler.h"

renderData rdata;

#ifdef _WIN32
HINSTANCE loadLib(int key)
{
        HINSTANCE lib_handle;

//    lib_handle = LoadLibrary(TEXT(("liblib" + std::to_string(key) + ".dll").c_str()));
        if (key == 1)
            lib_handle = LoadLibrary(TEXT("liblib1.dll"));
        if (key == 2)
            lib_handle = LoadLibrary(TEXT("liblib2.dll"));
        if (key == 3)
            lib_handle = LoadLibrary(TEXT("liblib3.dll"));
        if (!lib_handle)
        {
            std::cerr << "Cannot load library: " << TEXT("Lib") << TEXT(key) << " " << GetLastError() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib loaded" << std::endl;
        return lib_handle;
}

#else
void    *loadLib(int key)//linux
{
    void *lib_handle;
    char *err;

//        lib_handle = dlopen(((std::string)"libs/liblib" + std::to_string(key) + (std::string)".so").c_str(), RTLD_LAZY);//works
        if (key == 1)
            lib_handle = dlopen("libs/liblib1.dylib", RTLD_LAZY);//lib_handle = LoadLibrary(TEXT("liblib1.dll"));
        if (key == 2)
            lib_handle = dlopen("libs/liblib2.dylib", RTLD_LAZY);//lib_handle = LoadLibrary(TEXT("liblib2.dll"));
        if (key == 3)
            lib_handle = dlopen("libs/liblib3.dylib", RTLD_LAZY);//lib_handle = LoadLibrary(TEXT("liblib3.dll"));
        if (!lib_handle)
        {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib loaded" << std::endl;
        return (lib_handle);
}
#endif

void unloadLib(Engine* engine)
{
    #ifdef _WIN32
        FreeLibrary(engine->getLibHandle());
        engine->setLib(-1);
        std::cout << "Lib closed" << std::endl;
    #else
        dlclose(engine->getLibHandle());
        engine->setLib(0);
        std::cout << "Lib closed" << std::endl;
    #endif
}

void destroyInstance(Engine * engine)
{
    void (*fn)(void);

    #ifdef _WIN32
        fn = reinterpret_cast<void(*)(void)>(GetProcAddress(engine->getLibHandle(), "clean"));
    #else
        fn = reinterpret_cast<void(*)(void)>(dlsym(engine->getLibHandle(), "clean"));
    #endif
    if (!fn)
    {
        #ifdef _WIN32
            std::cerr << "Cannot load symbol clean " << GetLastError() << std::endl;
    #else
        std::cerr << "cannot load symbol clean " << dlerror() << std::endl;
    #endif
    }
    (*fn)();
    unloadLib(engine);
}

renderData update(Engine* engine, Player * player, Food * food)
{
    renderData (*fn)(renderData);
    int temp[2];
    int temp2[2];
    int x = 1;
    int y = 0;

    #ifdef _WIN32
        fn = reinterpret_cast<renderData(*)(renderData)>(GetProcAddress(engine->getLibHandle(), "render"));
    #else
        fn = reinterpret_cast<renderData(*)(renderData)>(dlsym(engine->getLibHandle(), "render"));
    #endif
    if (!fn)
    {
        #ifdef _WIN32
            std::cerr << "Cannot load symbol render " << GetLastError() << std::endl;
        #else

            std::cerr << "cannot load symbol render " << dlerror() << std::endl;
        #endif
    }
    temp[0] = rdata.playerBody[0][0];
    rdata.playerBody[0][0] = player->getPosX();
    temp[1] = rdata.playerBody[0][1];
    rdata.playerBody[0][1] = player->getPosY();
    for (int i = 1; i < rdata.playerBody.size(); i++)
    {
        while(!food->getVisible())
        {
            food->setPosX(std::rand() % engine->getWindow()->getObjWidth());
            food->setPosY(std::rand() % engine->getWindow()->getObjHeight());
            if (food->getPosX() != rdata.playerBody[x][y] && food->getPosY() != rdata.playerBody[x][y + 1])
                food->setVisible(true);
        }
        rdata.foodPosX = food->getPosX();
        rdata.foodPosY = food->getPosY();
        if (player->getPosX() == rdata.playerBody[x][y] && player->getPosY() == rdata.playerBody[x][y + 1])
        {
            std::cout << "Stop hitting yourself" << std::endl;
            destroyInstance(engine);
        }
        temp2[0] = rdata.playerBody[x][y];
        rdata.playerBody[x][y] = temp[0];
        ++y;
        temp2[1] = rdata.playerBody[x][y];
        rdata.playerBody[x][y] = temp[1];
        --y;
        ++x;
        temp[0] = temp2[0];
        temp[1] = temp2[1];
    }
    player->setPosX(player->getXDirection());
    rdata.playerPosX = player->getPosX();
    player->setPosY(player->getYDirection());
    rdata.playerPosY = player->getPosY();
    if (food->getVisible() && player->getPosX() == food->getPosX() && player->getPosY() == food->getPosY())
    {
        food->setVisible(false);
        rdata.playerBody.push_back(std::vector<int>(2));
        rdata.playerBody[rdata.playerBody.size() - 1][0] = rdata.playerBody[rdata.playerBody.size() - 2][0];
        rdata.playerBody[rdata.playerBody.size() - 1][1] = rdata.playerBody[rdata.playerBody.size() - 2][1];
    }
    if (rdata.playerPosX < 0 || rdata.playerPosX > engine->getWindow()->getObjWidth() - 1 || rdata.playerPosY < 0 || rdata.playerPosY > engine->getWindow()->getObjHeight() - 1)
        destroyInstance(engine);
    rdata = (*fn)(rdata);
    return rdata;
}

void initializeRenderer(Engine * engine)
{
    double (*fn)(renderData);

    #ifdef _WIN32
    fn = reinterpret_cast<double(*)(renderData)>(GetProcAddress(engine->getLibHandle(), "initialize"));
    if (!fn)
        std::cerr << "Cannot load symbol initialize " << GetLastError() << std::endl;
    #else
    fn = reinterpret_cast<double(*)(renderData)>(dlsym(engine->getLibHandle(), "initialize"));
    if (!fn)
        std::cerr << "Cannot load symbol initialize " << dlerror() << std::endl;
    #endif 
    (fn)(rdata);
}

void initializeGame(Engine * engine, Player * player)
{
    int x = 0;
    int y = 0;

    rdata.winWidth = engine->getWindow()->getObjWidth();
    rdata.winHeight = engine->getWindow()->getObjHeight();
    rdata.objWidth = 480 / engine->getWindow()->getObjWidth();
    rdata.objHeight = 480 / engine->getWindow()->getObjHeight();
    rdata.playerPosX = player->getPosX();
    rdata.playerPosY = player->getPosY();
    rdata.playerXDirection = 0;
    rdata.playerYDirection = -1;
    for (int i = 0; i <= 3; i++)
    {
        rdata.playerBody.push_back(std::vector<int>(2));
        rdata.playerBody[x][y] = player->getPosX();
        ++y;
        rdata.playerBody[x][y] = player->getPosY() + i;
        --y;
        ++x;
    }
}

int main(int ac, char * av[])
{
    srand(time(NULL));
    int width, height;

    if (ac != 3)
    {
        std::cerr << "Requires 2 parameters [WIDTH/HEIGHT]" << std::endl;
        exit(1);
    }

    width = atoi(av[1]);
    height = atoi(av[2]);
    rdata.ac = ac;
    rdata.av = av;
    Engine * engine = new Engine(width, height, width/2, height/2);
    Player * player = new Player(width/2, height/2);
    Food * food = new Food();
    engine->setLibHandle(loadLib(1));//only defined in #ifdef _WIN32; have to make it for linux.
    engine->setLib(1);
    initializeGame(engine, player);

    while (engine->getLib() != 0)
    {
        while (engine->getLib() == 1)
        {
            #ifdef _WIN32
                Sleep(50);
            #else
                usleep(50000);
            #endif
            if (!engine->getLib1())
            {
                initializeRenderer(engine);
                engine->setLib1(true);
            }

            if (rdata.key != 1 && rdata.key != 0)
            {
                if (rdata.key == 2 || rdata.key == 3)
                {
                    std::cout << "lib1" << std::endl;
                    destroyInstance(engine);
                    engine->setLib1(false);
                    engine->setLibHandle(loadLib(rdata.key));
                    engine->setLib(rdata.key);
                }
            }
            else
            {
                rdata = update(engine, player, food);
                rdata.dir = false;
                player->setXDirection(rdata.playerXDirection);
                player->setYDirection(rdata.playerYDirection);
            }

        }

//        while(engine->getLib() == 2)
//        {
//            if (engine->getKey() != 2 && engine->getKey() != 0) {
//                if (engine->getKey() == 1 || engine->getKey() == 3)
//                {
//                    unloadLib(engine);
//                    engine->setLibHandle(loadLib(engine->getKey()));
//                    engine->setLib(engine->getKey());
//                    engine->setKey(0);
//                }
//            }
//            else
//            {
//                rdata = update(engine, player, food);
//                engine->setKey(0);
//            }
//        }

        while(engine->getLib() == 3)
        {
            #ifdef _WIN32
                Sleep(50);
            #else
                usleep(50000);
            #endif
            if (!engine->getLib3())
            {
                rdata.key = 0;
                initializeRenderer(engine);
                engine->setLib3(true);
            }
            if (rdata.key != 3 && rdata.key != 0) {
                if (rdata.key == 1 || rdata.key == 2)
                {
                    std::cout << "lib1" << std::endl;
                    destroyInstance(engine);
                    engine->setLib3(false);
                    engine->setLibHandle(loadLib(rdata.key));
                    engine->setLib(rdata.key);
                }
            }
            else
            {
                rdata = update(engine, player, food);
                rdata.dir = false;
                player->setXDirection(rdata.playerXDirection);
                player->setYDirection(rdata.playerYDirection);
            }
        }
    }
    return 0;
}

