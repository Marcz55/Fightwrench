#include "grenade.h"
#include <iostream>

using namespace std;

grenade::grenade(double init_x, double init_y, double angle):projectile("grenade",init_x, init_y,10,angle)
{
    x_deceleration = cos(angle*0.0175)*5;
    y_deceleration = sin(angle*0.0175)*5;
    if (x_deceleration < 0)
    {
        x_deceleration = -x_deceleration;
    }
    if (y_deceleration < 0)
    {
        y_deceleration = -y_deceleration;
    }
    cout << x_deceleration << endl;
}

void grenade::update()
{
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
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
    cout << x_movement << endl;
}
