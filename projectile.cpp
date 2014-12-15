#include "projectile.h"
#include <iostream>
#include "gamefield.h"
using namespace std;

projectile::projectile(string bullet_name, double x, double y, int speed, double angle, int init_explosion_timer, int init_explosion_radius,int init_damage,class gamefield* init_gamefield):gameobject(bullet_name,x,y,speed,angle,init_gamefield)
{
    direction = angle;
    x_movement = speed*cos(direction*0.0175); //0.0175 ungefär pi/180
    y_movement = speed*sin(direction*0.0175);
    explosion_timer = init_explosion_timer;
    explosion_radius = init_explosion_radius;
    damage = init_damage;

    //Detta ska abra göras för granater
    if(name == "grenade")
    {
        x_deceleration = abs(cos(angle*0.0175)*0.1);
        y_deceleration = abs(sin(angle*0.0175)*0.1);

    }

}

void projectile::update()
{

    /*if((main_gamefield->get_collision_handler_pointer())->allowed_to_move_bullet(xpos,ypos,xpos + x_movement,ypos + y_movement,false,this))
    {
        xpos = xpos + x_movement;
        ypos = ypos + y_movement;

    }*/
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
    //Ska bara ske för grenade
   /* if (name == "grenade")
    {
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


    //Ska bara ske för projektiler som ska använda timer
    if (name == "grenade")
    {
        if (explosion_timer > 0)
        {
            explosion_timer -= 1;
        }
    }
    */
    return;

}
