//
// Created by Andromaleus on 2017-06-08.
//

#include "../includes/nibbler.h"

HINSTANCE   loadLib(int key)//linux
{
    HINSTANCE   lib_handle;

        lib_handle = dlopen(((std::string)"libs/liblib" + std::to_string(key) + ((std::string)(WIN32 ? ".dll" : ".so"))).c_str(), RTLD_LAZY);//works on linux might on windows.
        if (!lib_handle)
        {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib loaded" << std::endl;
        return (lib_handle);
}

void    unloadLib(Engine* engine)
{
        dlclose(engine->getLibHandle());
        engine->setLib(0);
        std::cout << "Lib closed" << std::endl;
}

void    update(Engine* engine)
{
    double (*fn)(Engine *);

    fn = reinterpret_cast<double(*)(Engine*)>(dlsym(engine->getLibHandle(), "render"));
    if (!fn)
            std::cerr << "cannot load symbol render" << dlerror() << std::endl;
    (*fn)(engine);
}

void    lib_selector(Engine *engine, int i, int j, int k)
{
    while (engine->getLib() == i)
    {
        if (engine->getKey() != i && engine->getKey() != 0)
        {
            if (engine->getKey() == j || engine->getKey() == k)
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
                exit(0);//same as return (0) from main?
            }
        }
        else
        {
            update(engine);//keyhooking of all libs should merely just change the engine->key variable.
            engine->setKey(0);
        }
        //will probably need a snake moving timer somewhere here. with a player->speed variable (to ratio clock).
    }
}

int     main(int ac, char *av[])
{
    int     width, height;

    if (ac != 3)
    {
        std::cerr << "Requires 2 parameters [WIDTH/HEIGHT]" << std::endl;
        exit(1);
    }
    width = atoi(av[1]);
    height = atoi(av[2]);
    Engine *engine = new Engine(width, height, width / 2, height / 2);
    engine->setLibHandle(loadLib(1));//only defined in #ifdef _WIN32; have to make it for linux.
    engine->setLib(1);
    while (engine->getLib() != 0)
    {
        lib_selector(engine, 1, 3, 2);//while lib1 is loaded
        lib_selector(engine, 2, 1, 3);//while lib2 is loaded
        lib_selector(engine, 3, 2, 1);//while lib3 is loaded
    }
    return (0);
}