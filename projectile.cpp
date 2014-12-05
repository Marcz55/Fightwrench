#include "projectile.h"
#include <math.h>
using namespace std;

projectile::projectile(string bullet_name, double x, double y, int speed, double angle):gameobject(bullet_name,x,y,speed,angle)
{
    direction = angle;
    x_movement = speed*cos(direction*0.0175); //0.0175 ungefär pi/180
    y_movement = speed*sin(direction*0.0175);

}

void projectile::update()
{
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
}
