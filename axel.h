#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle,
         collision_handler* init_collision_handler_pointer,class gamefield* init_gamefield):character("Axel",x,y,3,angle,"grenade",100,100,5,500,105,37,init_collision_handler_pointer,"char_1", init_gamefield){}
};

#endif // AXEL_H
