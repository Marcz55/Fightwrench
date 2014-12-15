#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "gameobject.h"
#include <cmath>
//
class projectile : public gameobject
{
public:
    virtual ~projectile() = default;
    projectile();
    projectile(std::string bullet_name, double x, double y,int speed, double angle, int init_explosion_timer, int init_explosion_radius,int init_damage, class gamefield* init_gamefield = nullptr);
    virtual void update() override;
    void test();
    int get_explosion_radius(){return explosion_radius;}
    int get_explosion_timer(){return explosion_timer;}
    int get_damage(){return damage;}
    double get_x_movement(){return x_movement;}
    double get_y_movement(){return y_movement;}

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
