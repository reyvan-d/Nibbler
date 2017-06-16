//
// Created by Andromaleus on 2017-06-08.
//

#ifndef NIBBLER_NIBBLER_H
#define NIBBLER_NIBBLER_H

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/types.h>
#endif

#include "window.class.hpp"
#include "engine.class.hpp"
#include "player.class.hpp"

#ifdef __cplusplus
}
#endif

struct renderData
{
    int winWidth;
    int winHeight;
    int playerPosX;
    int playerPosY;
    int objWidth;
    int objHeight;
    int playerDirection;
};

#endif //NIBBLER_NIBBLER_H
