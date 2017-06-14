//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "entity.class.hpp"

class Player : public Entity
{//this is most likely the worm :| ; thus any variables like speed, direction and length (etc) should probably go here.
    public:
        Player();
        Player(int xPos, int yPos);
        Player(const Player& player);
        void operator = (const Player& player);
        ~Player();

    private:
};

#endif
