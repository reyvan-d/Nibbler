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
            std::cerr << "Cannot load library: " << TEXT("Lib1") << std::endl;
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
        engine->setLib(0);
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
    exit(0);
}

renderData update(Engine* engine, Player * player)
{
    renderData (*fn)(renderData);

    #ifdef _WIN32
        fn = reinterpret_cast<double(*)(renderData)>(GetProcAddress(engine->getLibHandle(), "render"));
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
    player->setPosX(player->getXDirection());
    rdata.playerPosX = player->getPosX();
    player->setPosY(player->getYDirection());
    rdata.playerPosY = player->getPosY();
    if (rdata.playerPosX < 0 || rdata.playerPosX > engine->getWindow()->getObjWidth() - 1 || rdata.playerPosY < 0 || rdata.playerPosY > engine->getWindow()->getObjHeight() - 1)
        destroyInstance(engine);
    rdata = (*fn)(rdata);
    return rdata;
}

void initializeSDL(Engine * engine, Player * player)
{
    double (*fn)(renderData);

    rdata.winWidth = 640;
    rdata.winHeight = 480;
    rdata.objWidth = 480 / engine->getWindow()->getObjWidth();
    rdata.objHeight = 480 / engine->getWindow()->getObjHeight();
    rdata.playerPosX = player->getPosX();
    rdata.playerPosY = player->getPosY();
    #ifdef _WIN32
    fn = reinterpret_cast<double(*)(renderData)>(GetProcAddress(engine->getLibHandle(), "initialize"));
    if (!fn)
        std::cerr << "Cannot load symbol initialize " << GetLastError() << std::endl;
    #else
    fn = reinterpret_cast<double(*)(renderData)>(dlsym(engine->getLibHandle(), "initialize"));
    if (!fn)
        std::cerr << "Cannot load symbol initialize " << dlerror() << std::endl;
    #endif 
    (*fn)(rdata);
}

int main(int ac, char * av[])
{
    int width, height;

    if (ac != 3)
    {
        std::cerr << "Requires 2 parameters [WIDTH/HEIGHT]" << std::endl;
        exit(1);
    }

    width = atoi(av[1]);
    height = atoi(av[2]);
    Engine * engine = new Engine(width, height, width/2, height/2);
    Player * player = new Player(width/2, height/2);
    engine->setLibHandle(loadLib(1));//only defined in #ifdef _WIN32; have to make it for linux.
    engine->setLib(1);

    while (engine->getLib() != 0)
    {
        while (engine->getLib() == 1)
        {
            usleep(100000);
            if (!engine->getLib1())
            {
                initializeSDL(engine, player);
                engine->setLib1(true);
            }

            if (engine->getKey() != 1 && engine->getKey() != 0)
            {
                if (engine->getKey() == 2 || engine->getKey() == 3)
                {
                    unloadLib(engine);
                    engine->setLibHandle(loadLib(engine->getKey()));
                    engine->setLib(engine->getKey());
                    engine->setKey(0);
                    break;
                }
                if (engine->getKey() == -1)
                {
                    unloadLib(engine);
                    engine->setLib1(false);
                    return 0;
                }
            }
            else
            {
                rdata = update(engine, player);
                player->setXDirection(rdata.playerXDirection);
                player->setYDirection(rdata.playerYDirection);
                engine->setKey(0);
            }

        }

        while(engine->getLib() == 2)
        {
            if (engine->getKey() != 2 && engine->getKey() != 0) {
                if (engine->getKey() == 1 || engine->getKey() == 3)
                {
                    unloadLib(engine);
                    engine->setLibHandle(loadLib(engine->getKey()));
                    engine->setLib(engine->getKey());
                    engine->setKey(0);
                    break;
                }
                if (engine->getKey() == -1)
                {
                    unloadLib(engine);
                    return 0;
                }
            }
            else
            {
                rdata = update(engine, player);
                engine->setKey(0);
            }
        }

        while(engine->getLib() == 3)
        {
            if (engine->getKey() != 3 && engine->getKey() != 0) {
                if (engine->getKey() == 1 || engine->getKey() == 2)
                {
                    unloadLib(engine);
                    engine->setLibHandle(loadLib(engine->getKey()));
                    engine->setLib(engine->getKey());
                    engine->setKey(0);
                    break;
                }
                if (engine->getKey() == -1)
                {
                    unloadLib(engine);
                    return 0;
                }
            }
            else
            {
                rdata = update(engine, player);
                engine->setKey(0);
            }
        }

//        while(engine->getLib() == 3)
//        {
//            if (engine->getKey() != 3 && engine->getKey() != 0) {
//                if (engine->getKey() == 1 || engine->getKey() == 2)
//                {
//                    unloadLib(engine);
//                    loadLib(engine->getKey());
//                    engine->setLib(engine->getKey());
//                    engine->setKey(0);
//                    break;
//                }
//                if (engine->getKey() == -1)
//                {
//                    return 0;
//                }
//            }
//            else
//            {
//                update(engine);
//                engine->setKey(0);
//            }
//        }
    }
    return 0;
}

