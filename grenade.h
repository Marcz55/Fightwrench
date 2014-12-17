#ifndef GRENADE_H
#define GRENADE_H
#include "projectile.h"

class grenade : public projectile
{
public:
    grenade(double init_x, double init_y,double init_x_movement, double init_y_movement, double angle, class gamefield* init_gamefield, int damage, class character* character_pointer);
    virtual ~grenade()  override = default;
    grenade(const grenade&) = delete;
    grenade& operator=(const grenade&) = delete;

private:
    double x_deceleration;
    double y_deceleration;
    int explosion_timer = 10;
};

#endif // GRENADE_H
