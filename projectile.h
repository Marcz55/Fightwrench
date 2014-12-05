#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "gameobject.h"

class projectile : public gameobject
{
public:
    ~projectile() = default;
    projectile();
    projectile(std::string bullet_name, double x, double y,int speed, double angle);
    void update() override;

protected:
    double x_movement;
    double y_movement;
    int damage;
};

#endif // PROJECTILE_H
