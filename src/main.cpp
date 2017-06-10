//
// Created by Andromaleus on 2017-06-08.
//

#include "../includes/nibbler.h"

void loadLib1(Window * window)
{
    #ifdef WIN32
        HINSTANCE lib_handle;
    #else
        void * lib_handle;
    #endif
    double (*fn)(int *);
    int x;
    char * err;

    std::cout << window->getWidth() << " " << window->getHeight() << std::endl;
    window->setWidth(10);
    window->setHeight(15);
    #ifdef WIN32
        lib_handle = LoadLibrary(TEXT("liblib1.dll"));
        if (!lib_handle)
        {
            std::cerr << "Cannot load library: " << TEXT("Lib1") << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib1 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(GetProcAddress(lib_handle, "ctest1"));
        if (!fn)
        {
            std::cerr << "Cannot load symbol ctest1" << GetLastError() << std::endl;
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        FreeLibrary(lib_handle);
        std::cout << "Lib1 closed" << std::endl;
    #else
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
    #endif
    std::cout << window->getWidth() << " " << window->getHeight() << std::endl;
}

void loadLib2(Window * window)
{
    #ifdef WIN32
        HINSTANCE lib_handle;
    #else
        void * lib_handle;
    #endif
    double (*fn)(int *);
    int x;
    char * err;

    std::cout << window->getWidth() << " " << window->getHeight() << std::endl;
    window->setWidth(10);
    window->setHeight(15);
    #ifdef WIN32
        lib_handle = LoadLibrary(TEXT("liblib2.dll"));
        if (!lib_handle)
        {
            std::cerr << "Cannot load library: " << TEXT("Lib2") << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib2 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(GetProcAddress(lib_handle, "ctest1"));
        if (!fn)
        {
            std::cerr << "Cannot load symbol ctest1" << GetLastError() << std::endl;
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        FreeLibrary(lib_handle);
        std::cout << "Lib2 closed" << std::endl;
    #else
        lib_handle = dlopen("libs/liblib2.dylib", RTLD_LAZY);
        if (!lib_handle)
        {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib2 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(dlsym(lib_handle, "ctest1"));
        if ((err = dlerror()) != NULL)
        {
            std::cerr << err << std::endl;
            exit(1);
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        dlclose(lib_handle);
        std::cout << "Lib2 closed" << std::endl;
    #endif
    std::cout << window->getWidth() << " " << window->getHeight() << std::endl;
}

void loadLib3(Window * window)
{
    #ifdef WIN32
        HINSTANCE lib_handle;
    #else
        void * lib_handle;
    #endif
    double (*fn)(int *);
    int x;
    char * err;

    #ifdef WIN32
        lib_handle = LoadLibrary(TEXT("liblib3.dll"));
        if (!lib_handle)
        {
            std::cerr << "Cannot load library: " << TEXT("Lib3") << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib3 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(GetProcAddress(lib_handle, "ctest1"));
        if (!fn)
        {
            std::cerr << "Cannot load symbol ctest1" << GetLastError() << std::endl;
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        FreeLibrary(lib_handle);
        std::cout << "Lib3 closed" << std::endl;
    #else
        lib_handle = dlopen("libs/liblib3.dylib", RTLD_LAZY);
        if (!lib_handle)
        {
            std::cerr << dlerror() << std::endl;
            exit(1);
        }
        else
            std::cout << "Lib3 loaded" << std::endl;
        fn = reinterpret_cast<double(*)(int*)>(dlsym(lib_handle, "ctest1"));
        if ((err = dlerror()) != NULL)
        {
            std::cerr << err << std::endl;
            exit(1);
        }
        (*fn)(&x);
        std::cout << "Val x = " << x << std::endl;
        dlclose(lib_handle);
        std::cout << "Lib3 closed" << std::endl;
    #endif
    std::cout << window->getWidth() << " " << window->getHeight() << std::endl;

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
    Window * window = new Window(width, height);
    std::cout << "Window generated with a width of " << window->getWidth() << " and a height of " << window->getHeight() << " sections." << std::endl;

    loadLib1(window);
    loadLib2(window);
    loadLib3(window);
    std::cout << "Window modified to a width of " << window->getWidth() << " and a height of " << window->getHeight() << " sections." << std::endl;

    return 0;
}

