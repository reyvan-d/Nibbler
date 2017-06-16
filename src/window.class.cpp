//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "../includes/window.class.hpp"

Window::Window()
{
    this->objWidth = 25;
    this->objHeight = 25;
}

Window::Window(int width, int height) : objWidth(width), objHeight(height)
{

}

Window::Window(const Window& window)
{
    *this = window;
}

void Window::operator = (const Window& window)
{
    this->objWidth = window.objWidth;
    this->objHeight = window.objHeight;
}

Window::~Window()
{

}

int Window::getWidth()
{
    return this->width;
}

int Window::getHeight()
{
    return this->height;
}

int Window::getObjWidth()
{
    return this->objWidth;
}

int Window::getObjHeight()
{
    return this->objHeight;
}

void Window::setWidth(int width)
{
    this->width = width;
}

void Window::setHeight(int height)
{
    this->height = height;
}

void Window::setObjWidth(int width)
{
    this->objWidth = width;
}

void Window::setObjHeight(int height)
{
    this->objHeight = height;
}