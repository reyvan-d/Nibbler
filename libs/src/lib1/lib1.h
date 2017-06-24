//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef LIB1_H
#define LIB1_H

#include "../../../includes/nibbler.h"
#include <SDL.h>

#ifdef __cplusplus
extern "C"
{
    #ifdef _WIN32
    __declspec(dllexport) void initialize(renderData rdata);
    __declspec(dllexport) renderData render(renderData rdata);
    __declspec(dllexport) void clean();
    #endif
}
#endif

//library code goes here

#ifndef _WIN32

//Add exported functions for OSX
void initialize(renderData rdata);
renderData render(renderData rdata);
void clean();

#endif

//struct data
//{
//    int winWidth;
//    int winHeight;
//    int playerPosX;
//    int playerPosY;
//};

#endif