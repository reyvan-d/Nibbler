//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "../includes/window.class.hpp"

Window::Window()
{
    this->width = 25;
    this->height = 25;
}

Window::Window(int width, int height) : width(width), height(height)
{

}

Window::Window(const Window& window)
{
    *this = window;
}

void Window::operator = (const Window& window)
{
    this->width = window.width;
    this->height = window.height;
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

void Window::setWidth(int width)
{
    this->width = width;
}

void Window::setHeight(int height)
{
    this->height = height;
}