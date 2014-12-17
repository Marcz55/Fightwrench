#ifndef MARCUS_H
#define MARCUS_H
#include "character.h"

class marcus : public character
{
public:
    marcus(int x, int y,double angle,
           class gamefield* init_gamefield):character("Marsus","body2",x,y,2.5,angle,"bullet",20,85,30,100,90,34,"char_2", init_gamefield, 2){}
    virtual ~marcus() override = default;
    marcus(const marcus&) = delete;
    marcus& operator=(const marcus&) = delete;
};

#endif // MARCUS_H
