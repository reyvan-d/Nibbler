//
// Created by Andromaleus on 2017-06-08.
//

#ifndef NIBBLER_NIBBLER_H
#define NIBBLER_NIBBLER_H

#ifdef _WIN32
    #include <direct.h>
    #include <windows.h>
    #define dlclose(A) FreeLibrary(A)
    #define dlsym(A, B) GetProcAddress(A, B)
    #define dlerror() GetLastError()
    #define RTLD_LAZY 0 //only exists on __UNIX__
    #define dlopen(A, B) LoadLibrary(TEXT(A))//dlopen is unix specific so now it can be used the same on windows too :|.
    #define WIN32 1//true that it is windows
#else
    #include <dlfcn.h>
    #include <sys/types.h>
    #define HINSTANCE void *
    #define WIN32 0//false that it is windows
#endif

#include <iostream>
#include "window.class.hpp"
#include "engine.class.hpp"
#include "player.class.hpp"

#endif //NIBBLER_NIBBLER_H
