//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "nibbler.h"
#include "entity.class.hpp"

class Player : public Entity {
    public:
        Player();
        Player(int xPos, int yPos);
        Player(const Player& player);
        void operator = (const Player& player);
        ~Player();

        int getPosX();
        int getPosY();
        int getXDirection();
        int getYDirection();
        std::vector<Entity> getBody();
        void setPosX(int posX);
        void setPosY(int posY);
        void setXDirection(int dirX);
        void setYDirection(int dirY);
    void    setscore(int score);
    int     getscore();

    private:
        int xDirection;
        int yDirection;
        int score;
        std::vector<Entity> bodyPart;
};

#endif
