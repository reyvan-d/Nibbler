//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef LIB1_H
#define LIB1_H

#include "../../../includes/nibbler.h"

#ifdef __cplusplus
extern "C" {
#endif

//library code goes here
#ifdef _WIN32
__declspec(dllexport) void initialize(renderData rdata);
__declspec(dllexport) void render(Engine * engine);
#else

//Add exported functions for OSX

#endif

#ifdef __cplusplus
}
#endif

//struct data
//{
//    int winWidth;
//    int winHeight;
//    int playerPosX;
//    int playerPosY;
//};

#endif