//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "../includes/player.class.hpp"

Player::Player()
{
    this->xPos = 10;
    this->yPos = 10;
}

Player::Player(int xPos, int yPos) : Entity(xPos, yPos)
{

}

Player::Player(const Player& player)
{
    *this = player;
}

void Player::operator = (const Player& player)
{
    this->xPos = player.xPos;
    this->yPos = player.yPos;
}

Player::~Player()
{

}