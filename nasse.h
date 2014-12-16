#ifndef NASSE_H
#define NASSE_H
#include "character.h"

class nasse : public character
{
public:
    nasse(int x, int y,double angle,
           class gamefield* init_gamefield):character("Nassehuvud","body3",x,y,2,angle,"rocket",20,100,1,200,90,34,"Nasse", init_gamefield, 3){}
};

#endif // NASSE_H
