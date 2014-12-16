#ifndef BULLET_H
#define BULLET_H
#include "projectile.h"
class bullet : public projectile
{
public:
    bullet(double init_x, double init_y, double angle,class gamefield* init_gamefield, int damage,class character* character_pointer):projectile("bullet",init_x, init_y,10,angle,1,0,damage,init_gamefield,character_pointer){}
    void update() override;
    virtual ~bullet() = default;
};

#endif // BULLET_H
