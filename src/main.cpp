//
// Created by Andromaleus on 2017-06-08.
//

#include "../includes/nibbler.h"

int main(int ac, char * av[])
{
    void * lib_handle;
    double (*fn)(int *);
    int x;
    char * err;
    if (ac != 3)
    {
        std::cerr << "Requires 2 parameters [WIDTH/HEIGHT]" << std::endl;
        exit(1);
    }

    lib_handle = dlopen("libs/liblib1.dylib", RTLD_LAZY);
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
    return 0;
}

