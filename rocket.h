#ifndef ROCKET_H
#define ROCKET_H
#include "projectile.h"

class rocket : public projectile
{
public:
    rocket(double init_x, double init_y, double angle,class gamefield* init_gamefield, int damage):projectile("rocket",init_x, init_y,0,angle,1,1,damage,init_gamefield){}
};

#endif // ROCKET_H
