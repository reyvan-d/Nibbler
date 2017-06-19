//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "../includes/entity.class.hpp"

Entity::Entity()
{
    this->xPos = 3;
    this->yPos = 3;
}

Entity::Entity(int xPos, int yPos) : xPos(xPos), yPos(yPos)
{

}

Entity::Entity(const Entity& entity)
{
    *this = entity;
}

void Entity::operator = (const Entity& entity)
{
    this->xPos = entity.xPos;
    this->yPos = entity.yPos;
}

Entity::~Entity()
{

}

int Entity::getPosX()
{
    return this->xPos;
}

int Entity::getPosY()
{
    return this->yPos;
}

void Entity::setPosX(int posx)
{
    this->xPos = posx;
}

void Entity::setPosY(int posy)
{
    this->yPos = posy;
}