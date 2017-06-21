//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef LIB3_H
#define LIB3_H

#include "../../../includes/nibbler.h"
#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>

#ifdef __cplusplus
extern "C" {
#endif

//library code goes here
void initialize(renderData rdata);
renderData render(renderData rdata);
void clean();

#ifdef __cplusplus
}
#endif

#endif