#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle, std::vector<projectile>* init_projectile_vector,
         soundhandler* init_soundhandler):character("Axel",x,y,3,angle,"grenade",init_projectile_vector,100,init_soundhandler,100,5,500){}
};

#endif // AXEL_H
