#ifndef MARCUS_H
#define MARCUS_H
#include "character.h"

class marcus : public character
{
public:
    marcus(std::string marcus_name, int x, int y,int speed, double angle):character(marcus_name,x,y,speed,angle){}
};

#endif // MARCUS_H
