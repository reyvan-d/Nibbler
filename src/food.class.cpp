//
// Created by Andromaleus on 2017-06-19.
//

#include "../includes/food.class.hpp"

Food::Food()
{
    this->xPos = 15;
    this->yPos = 15;
    this->visible = false;
}

Food::Food(int xPos, int yPos) : Entity(xPos, yPos)
{
    this->visible = false;
}

Food::Food(const Food& food) : Entity(food)
{
}

void Food::operator = (const Food& food)
{
    this->xPos = food.xPos;
    this->yPos = food.yPos;
}

Food::~Food()
{

}

int Food::getPosX()
{
    return this->xPos;
}

int Food::getPosY()
{
    return this->yPos;
}

void Food::setPosX(int posX)
{
    this->xPos = posX;
}

void Food::setPosY(int posY)
{
    this->yPos = posY;
}

void Food::setVisible(bool visible)
{
    this->visible = visible;
}

bool Food::getVisible()
{
    return this->visible;
}
