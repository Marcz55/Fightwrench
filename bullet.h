#ifndef BULLET_H
#define BULLET_H
#include "projectile.h"

class bullet : public projectile
{
public:
    bullet(double init_x, double init_y, double angle):projectile("bullet",init_x, init_y,10,angle,1,0){}
    void update() override;
    virtual ~bullet() override = default;
};

#endif // BULLET_H
