//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

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
    private:
};

#endif
