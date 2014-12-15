#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle,
         class gamefield* init_gamefield):character("Axel",x,y,3,angle,"grenade",100,100,5,500,105,37,"char_1", init_gamefield, 5){}
};

#endif // AXEL_H
