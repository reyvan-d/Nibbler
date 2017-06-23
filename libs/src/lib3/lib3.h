//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef LIB3_H
#define LIB3_H

#include "../../../includes/nibbler.h"
#include <glew.h>
#include <freeglut.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
    __declspec(dllexport) void initialize(renderData rdata);
    __declspec(dllexport) void LoadTextureRAW(GLuint texture, const char *filename, int wrap, int width, int height);
    __declspec(dllexport) void renderScreen();
    __declspec(dllexport) void handleResize(int w, int h);
    __declspec(dllexport) void handleKeypress(unsigned char key, int x, int y);
    __declspec(dllexport) void specialInput(int key, int x, int y);
    __declspec(dllexport) renderData render(renderData rdata);
    __declspec(dllexport) void clean();
#else
    void initialize(renderData rdata);
    void LoadTextureRAW(GLuint texture, const char *filename, int wrap, int width, int height);
    void renderScreen();
    void handleResize(int w, int h);
    void handleKeypress(unsigned char key, int x, int y);
    void specialInput(int key, int x, int y);
    renderData render(renderData rdata);
    void clean();
#endif

#ifdef __cplusplus
}
#endif

#endif