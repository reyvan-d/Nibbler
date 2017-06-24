//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "../includes/player.class.hpp"

Player::Player()
{
    this->xPos = 10;
    this->yPos = 10;
    this->xDirection = 0;
    this->yDirection = -1;
    this->bodyPart.push_back({this->xPos, this->yPos - 1});
    this->bodyPart.push_back({this->bodyPart[0].getPosX(), this->bodyPart[0].getPosY() - 1});
}

Player::Player(int xPos, int yPos) : Entity(xPos, yPos)
{
    this->xDirection = 0;
    this->yDirection = -1;
}

Player::Player(const Player& player) : Entity(player)
{
}

void Player::operator = (const Player& player)
{
    this->xPos = player.xPos;
    this->yPos = player.yPos;
}

Player::~Player()
{

}

int Player::getPosX()
{
    return this->xPos;
}

int Player::getPosY()
{
    return this->yPos;
}

void Player::setPosX(int posX)
{
    this->xPos += posX;
}

void Player::setPosY(int posY)
{
    this->yPos += posY;
}

int Player::getXDirection()
{
    return this->xDirection;
}

int Player::getYDirection()
{
    return this->yDirection;
}

void Player::setXDirection(int dirX)
{
    this->xDirection = dirX;
}

void Player::setYDirection(int dirY)
{
    this->yDirection = dirY;
}

std::vector<Entity> Player::getBody()
{
    return this->bodyPart;
}

int     Player::getscore()
{
    return (this->score);
}

void    Player::setscore(int score)
{
    this->score = score;
}