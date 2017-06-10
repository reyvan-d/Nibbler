//
// Created by Andromaleus on 2017-06-10.
//

#include "../includes/engine.class.hpp"

Engine::Engine()
{
    this->window = new Window();
    this->cLib = 1;
    this->key = 0;
    Player * player = new Player();
}

Engine::Engine(int width, int height, int pxPos, int pyPos)
{
    this->window = new Window(width, height);
    this->cLib = 1;
    this->key = 0;
    Player * player = new Player(pxPos, pyPos);
}

Engine::Engine(const Engine& engine)
{
    *this = engine;
}

void Engine::operator = (const Engine& engine)
{
}

Engine::~Engine()
{

}

Window* Engine::getWindow()
{
    return this->window;
}

int Engine::getKey()
{
    return this->key;
}

int Engine::getLib()
{
    return this->cLib;
}

void Engine::setLib(int lib)
{
    this->cLib = lib;
}

void Engine::setKey(int key)
{
    this->key = key;
}

#ifdef _WIN32
    HINSTANCE Engine::getLibHandle()
    {
        return this->lib_handle;
    }

    void Engine::setLibHandle(HINSTANCE lib_handle)
    {
        this->lib_handle = lib_handle;
    }
#else
    void * Engine::getLibHandle()
    {
        return this->lib_handle;
    }

    void Engine::setLibHandle(void * lib_handle)
    {
        this->lib_handle = lib_handle;
    }
#endif