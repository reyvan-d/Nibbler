//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

class Entity {
    public:
        Entity();
        Entity(int xPos, int yPos);
        Entity(const Entity& entity);
        void operator = (const Entity& entity);
        ~Entity();

        int getPosX();
        int getPosY();
        void setPosX(int posx);
        void setPosY(int posy);
    protected:
        int xPos;
        int yPos;
};

#endif
