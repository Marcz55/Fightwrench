#ifndef MARCUS_H
#define MARCUS_H
#include "character.h"

class marcus : public character
{
public:
    marcus(int x, int y,double angle,
           class gamefield* init_gamefield):character("Marsus","body2",x,y,2,angle,"bullet",20,100,30,100,90,34,"char_2", init_gamefield, 3){}
};

#endif // MARCUS_H
