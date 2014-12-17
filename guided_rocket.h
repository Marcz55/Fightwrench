#ifndef GUIDED_ROCKET_H
#define GUIDED_ROCKET_H
#include "projectile.h"

class guided_rocket : public projectile
{
public:
    guided_rocket(double init_x, double init_y,double init_x_movement, double init_y_movement, double angle,class gamefield* init_gamefield, int damage,class character* character_pointer):projectile("guided rocket",init_x, init_y,init_x_movement,init_y_movement,5,angle,1,1,damage,init_gamefield,character_pointer){}
    guided_rocket(const guided_rocket&) = delete;
    guided_rocket& operator=(const guided_rocket&) = delete;
    virtual ~guided_rocket() override = default;
};


#endif // GUIDED_ROCKET_H
