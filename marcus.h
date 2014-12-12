#ifndef MARCUS_H
#define MARCUS_H
#include "character.h"

class marcus : public character
{
public:
    marcus(int x, int y,double angle, std::vector<projectile>* init_projectile_vector,
           soundhandler* init_soundhandler, collision_handler* init_collision_handler_pointer):character("Marsus",x,y,2,angle,"bullet",init_projectile_vector,20,init_soundhandler,100,30,100,105,37,init_collision_handler_pointer){}
};

#endif // MARCUS_H
