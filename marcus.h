#ifndef MARCUS_H
#define MARCUS_H
#include "character.h"

class marcus : public character
{
public:
    marcus(int x, int y,double angle,
           collision_handler* init_collision_handler_pointer, class gamefield* init_gamefield):character("Marsus",x,y,2,angle,"bullet",20,100,30,100,105,37,init_collision_handler_pointer,"char_2", init_gamefield, 3){}
};

#endif // MARCUS_H
