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
    projectile(std::string bullet_name, double x, double y,double init_x_movement,double init_y_movement,int speed, double angle, int init_explosion_timer, double init_explosion_radius,int init_damage, class gamefield* init_gamefield = nullptr,class character* character_pointer = nullptr);
    virtual void update() override;
    void test();
    double get_explosion_radius(){return explosion_radius;}
    int get_explosion_timer(){return explosion_timer;}
    int get_damage(){return damage;}
    double get_x_movement(){return x_movement;}
    double get_y_movement(){return y_movement;}
    void set_x_movement(double value){x_movement = value;}
    void set_y_movement(double value){y_movement = value;}
    void set_x_position(double value){xpos = value;}
    void set_y_position(double value){ypos = value;}
    void set_deceleration();
    class character* get_owner_pointer();
    projectile* get_projectile_pointer(){return this;}

    void turn(int turn_direction){direction += turn_direction;}



protected:
    double x_movement;
    double y_movement;
    int damage;
    double explosion_radius = 0;
    int explosion_timer = 1;
    double x_deceleration = 0;
    double y_deceleration = 0;
   class character* character_owner_pointer;
};

#endif // PROJECTILE_H
