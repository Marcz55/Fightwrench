#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle, std::vector<projectile>* init_projectile_vector, soundhandler* init_soundhandler):character("Axel",x,y,3,angle,"grenade",init_projectile_vector,10,init_soundhandler){}
};

#endif // AXEL_H
