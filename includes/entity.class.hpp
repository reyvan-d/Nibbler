//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

class Entity
{//this sounds like the object spawning and food(which is probably considered an object) class.
    // (depending on how one chooses to go about this) 2d map(object data) would probably be placed here.
    public:
        Entity();
        Entity(int xPos, int yPos);
        Entity(const Entity& entity);
        void operator = (const Entity& entity);
        ~Entity();

    protected:
        int xPos;
        int yPos;
};

#endif
