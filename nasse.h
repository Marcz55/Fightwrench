#ifndef NASSE_H
#define NASSE_H
#include "character.h"

class nasse : public character
{
public:
    nasse(int x, int y,double angle,
           class gamefield* init_gamefield):character("Nassehuvud",x,y,2,angle,"bullet",20,100,30,100,105,37,"Nasse", init_gamefield, 3){}
};

#endif // NASSE_H
