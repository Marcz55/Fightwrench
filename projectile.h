#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "gameobject.h"
#include <cmath>

class projectile : public gameobject
{
public:
    virtual ~projectile() = default;
    projectile();
    projectile(std::string bullet_name, double x, double y,int speed, double angle, int init_explosion_timer, int init_explosion_radius, class gamefield* init_gamefield = nullptr);
    void update() override;
    void test();
    int get_explosion_radius(){return explosion_radius;}
    int get_explosion_timer(){return explosion_timer;}

protected:
    double x_movement;
    double y_movement;
    int damage;
    int explosion_radius = 0;
    int explosion_timer = 1;
    double x_deceleration = 0;
    double y_deceleration = 0;
};

#endif // PROJECTILE_H
