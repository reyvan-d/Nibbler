//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#include "lib1.h"

void render(Engine * engine)
{
    //-get a key here and set it into engine->key
    //-if key is 'specific key' then engine->player->setdirection (or something like that): should change.

    //-visuals would probably be rendered around about here. so:
    //  loop through all snake length links and see if head == any of those(GAME END).
    //  furthermore: if head is out of bounds(from the width and height or oposite ends) then (GAME END).

    //the fundemental complexity would lie in the 3d graphics part where extra variables may also be required,
    //  i.e: camera data, object data(i.e textures and vertex points etc) (etc(cannot think of anything else at the moment)).
    std::cout << "lib1\n";
}