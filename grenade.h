#ifndef GRENADE_H
#define GRENADE_H
#include "projectile.h"

class grenade : public projectile
{
public:
    grenade(double init_x, double init_y, double angle, class gamefield* init_gamefield, int damage);
    virtual ~grenade()  override = default;

private:
    double x_deceleration;
    double y_deceleration;
    int explosion_timer = 10;
};

#endif // GRENADE_H
