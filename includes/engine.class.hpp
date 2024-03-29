//
// Created by Andromaleus on 2017-06-10.
//

#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include "nibbler.h"

class Engine {
    public:
        Engine();
        Engine(int width, int height, int pxPos, int pyPos);
        Engine(const Engine& engine);
        void operator = (const Engine& engine);
        ~Engine();

        Window *getWindow();
        int getKey();
        int getLib();
        void setLib(int lib);
        void setKey(int key);
        bool getLib1();
        bool getLib2();
        bool getLib3();
        void setLib1(bool init);
        void setLib2(bool init);
        void setLib3(bool init);

        #ifdef _WIN32
            void setLibHandle(HINSTANCE lib_handle);
            HINSTANCE getLibHandle();
        #else
            void setLibHandle(void *lib_handle);
            void *getLibHandle();
        #endif
    protected:
        Window* window;
        int key;
        int cLib;
        bool lib1;
        bool lib2;
        bool lib3;
        #ifdef _WIN32
            HINSTANCE lib_handle;
        #else
            void* lib_handle;
        #endif
};

#endif