//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef LIB2_H
#define LIB2_H

#include "../../../includes/nibbler.h"
#include "featured_renderer.h"
#include <SFML/Graphics.hpp>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
__declspec(dllexport) void initialize(renderData rdata);
__declspec(dllexport) renderData render(renderData rdata);
__declspec(dllexport) void clean();
#else
//#include <epoxy/gl.h>
//#include <epoxy/glx.h>

void initialize(renderData rdata);
renderData render(renderData rdata);
void clean();
#endif

#ifdef __cplusplus
}
#endif

#endif