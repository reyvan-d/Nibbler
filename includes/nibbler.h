//
// Created by Andromaleus on 2017-06-08.
//

#ifndef NIBBLER_NIBBLER_H
#define NIBBLER_NIBBLER_H

#ifdef _WIN32
    #include <direct.h>
    #include <windows.h>
#else
    #include <dlfcn.h>
    #include <sys/types.h>
#endif

#include <iostream>
#include <SDL.h>
#include "window.class.hpp"
#include "engine.class.hpp"
#include "player.class.hpp"

#endif //NIBBLER_NIBBLER_H
