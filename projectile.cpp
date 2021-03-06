#include "projectile.h"
#include <iostream>
#include "gamefield.h"
using namespace std;

projectile::projectile(string bullet_name, double x, double y,double init_x_movement,double init_y_movement, int speed, double angle, int init_explosion_timer, double init_explosion_radius, int init_damage, class gamefield* init_gamefield, character *character_pointer):gameobject(bullet_name,x,y,speed,angle,init_gamefield)
{
    direction = angle;
    x_movement = speed*cos(direction*0.0175) + init_x_movement; //0.0175 ungefär pi/180
    y_movement = speed*sin(direction*0.0175) + init_y_movement;
    explosion_timer = init_explosion_timer;
    explosion_radius = init_explosion_radius;
    damage = init_damage;
    character_owner_pointer = character_pointer;
    //Detta ska abra göras för granater
    if(name == "grenade")
    {
        set_deceleration();
    }

    if(name == "rocket")
    {
        x_deceleration = cos(angle*0.0175)*0.1;
        y_deceleration = sin(angle*0.0175)*0.1;

    }


}


void projectile::set_deceleration()
{
    double x_component = abs(x_movement)/sqrt(pow(x_movement,2) + pow(y_movement,2));
    double y_component = abs(y_movement)/sqrt(pow(x_movement,2) + pow(y_movement,2));
    x_deceleration = x_component*0.1;
    y_deceleration = y_component*0.1;
}

void projectile::update()
{
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
    //Ska bara ske för grenade
    if (name == "grenade")
    {
        set_deceleration();
        if (abs(x_movement) <= x_deceleration)
        {
            x_movement = 0;
        }
        if (abs(y_movement) <= y_deceleration)
        {
            y_movement = 0;
        }
        if (x_movement > 0)
        {
            x_movement = x_movement - x_deceleration;
        }
        if (x_movement < 0)
        {
            x_movement = x_movement + x_deceleration;
        }
        if (y_movement > 0)
        {
            y_movement = y_movement - y_deceleration;
        }
        if (y_movement < 0)
        {
            y_movement = y_movement + y_deceleration;
        }
    }

    if (name == "rocket")
    {
        x_movement += x_deceleration;
        y_movement += y_deceleration;
    }


    //Ska bara ske för projektiler som ska använda timer
    if (name == "grenade")
    {
        if (explosion_timer > 0)
        {
            explosion_timer -= 1;
        }
    }

    if (name == "guided rocket")
    {
        x_movement = speed*cos(direction*0.0175);
        y_movement = speed*sin(direction*0.0175);
    }
    return;

}
class character* projectile::get_owner_pointer()
{
    return character_owner_pointer;
}
