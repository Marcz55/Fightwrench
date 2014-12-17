#ifndef NASSE_H
#define NASSE_H
#include "character.h"

class nasse : public character
{
public:
    nasse(int x, int y,double angle,
           class gamefield* init_gamefield):character("Nassehuvud","body3",x,y,1.5,angle,"rocket",20,150,1,200,90,34,"Nasse", init_gamefield, 20){}
    virtual ~nasse() override = default;
    nasse(const nasse&) = delete;
    nasse& operator=(const nasse&) = delete;
};

#endif // NASSE_H
