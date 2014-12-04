#ifndef AXEL_H
#define AXEL_H
#include "character.h"

class axel : public character
{
public:
    axel(std::string axel_name, int x, int y,int speed, double angle):character(axel_name,x,y,speed,angle){}
};

#endif // AXEL_H
