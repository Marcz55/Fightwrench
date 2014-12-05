#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(int x, int y, double angle, std::vector<projectile>* init_projectile_vector):character("Axel",x,y,3,angle,"bullet",init_projectile_vector,10){}
};

#endif // AXEL_H
