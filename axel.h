#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle,
         class gamefield* init_gamefield):character("Axel","body1",x,y,3,angle,"grenade",100,100,5,500,90,34,"char_1", init_gamefield, 5){}
};

#endif // AXEL_H
