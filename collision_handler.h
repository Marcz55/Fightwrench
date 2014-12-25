//Joakim Mörhed har skrivit Collision_handler.
//Collision_handler tar hand om kollisioner samt deras effekter.


#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include <vector>
#include "character.h"
#include "cover.h"
#include "gamefield.h"
#include <cmath>
#include "gamefield.h"
#include <iterator>
#include "projectile.h"
#include "bullet.h"
#include <iostream>
using namespace std;

class collision_handler
{
public:
    collision_handler(class gamefield*);
    ~collision_handler() = default;
    collision_handler(const collision_handler&) = delete;
    collision_handler& operator=(const collision_handler&) = delete;



    bool allowed_to_move_rectangle(vector<double>,character*);
    bool allowed_to_move_rectangle(vector<double>,cover*);
    bool allowed_to_move_circle(double,double,int);
    bool allowed_to_move_bullet(double, double, double, double, bool, double, double, class character*, class projectile*);
    void apply_explosion_damage(double, double, int, int);

private:
    class gamefield* gamefield_pointer;
    int window_height;
    int window_width;

};

#endif // COLLISION_HANDLER_H
