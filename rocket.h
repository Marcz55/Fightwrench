#ifndef ROCKET_H
#define ROCKET_H
#include "projectile.h"

class rocket : public projectile
{
public:
    rocket(double init_x, double init_y,double init_x_movement, double init_y_movement, double angle,class gamefield* init_gamefield, int damage,class character* character_pointer):projectile("rocket",init_x, init_y,init_x_movement,init_y_movement,0,angle,1,1,damage,init_gamefield,character_pointer){}
    rocket(const rocket&) = delete;
    rocket& operator=(const rocket&) = delete;
    virtual ~rocket() override = default;
};

#endif // ROCKET_H
