#include "projectile.h"
#include <math.h>
using namespace std;

projectile::projectile(string bullet_name, double x, double y, int speed, double angle):gameobject(bullet_name,x,y,speed,angle)
{
    direction = angle;
    x_movement = speed*cos(direction);
    y_movement = speed*sin(direction);

}

void projectile::update()
{
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
}
