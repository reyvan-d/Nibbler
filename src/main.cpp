//
// Created by Andromaleus on 2017-06-08.
//

#include "../includes/nibbler.h"

#ifdef _WIN32
HINSTANCE loadLib(int key)
{
    #ifdef _WIN32
        HINSTANCE lib_handle;
    #else
        void * lib_handle;
        char * err;
    #endif

    #ifdef _WIN32
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
            std::cout << "Lib1 loaded" << std::endl;
        return lib_handle;
    #else
        lib_handle = dlopen("libs/liblib1.so", RTLD_LAZY);
        if (!lib_handle)
        {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib1 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(dlsym(lib_handle, "ctest1"));
        if ((err = dlerror()) != NULL)
        {
            std::cerr << err << std::endl;
            exit(1);
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        dlclose(lib_handle);
        std::cout << "Lib1 closed" << std::endl;
    #endif
}

#else

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

void update(Engine* engine)
{
    double (*fn)(int *);
    int x;

    fn = reinterpret_cast<double(*)(int*)>(GetProcAddress(engine->getLibHandle(), "render"));
    if (!fn)
    {
        std::cerr << "Cannot load symbol render" << GetLastError() << std::endl;
    }
    (*fn)(&x);
    std::cout << "Val x = " << x << std::endl;
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
    engine->setLibHandle(loadLib(1));
    engine->setLib(1);

    while (engine->getLib() != 0) {

        while(engine->getLib() == 1)
        {
            if (engine->getKey() != 1 && engine->getKey() != 0) {
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
                    return 0;
                }
            }
            else
            {
                update(engine);
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
                update(engine);
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
                update(engine);
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

