//
// Created by Andromaleus on 2017-06-19.
//

#ifndef FOOD_CLASS_H
#define FOOD_CLASS_H

#include "nibbler.h"
#include "entity.class.hpp"

class Food : public Entity {
    public:
        Food();
        Food(int xPos, int yPos);
        Food(const Food& food);
        void operator = (const Food& food);
        ~Food();

        int getPosX();
        int getPosY();
        bool getVisible();
        void setPosX(int posX);
        void setPosY(int posY);
        void setVisible(bool visible);
    private:
        bool visible;
};

#endif