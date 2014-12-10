#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "gameobject.h"
#include <cmath>

class projectile : public gameobject
{
public:
    ~projectile() = default;
    projectile();
    projectile(std::string bullet_name, double x, double y,int speed, double angle);
    virtual void update() override;

protected:
    double x_movement;
    double y_movement;
    int damage;
    double x_deceleration = 0;
    double y_deceleration = 0;
};

#endif // PROJECTILE_H
