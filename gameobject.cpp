#include "gameobject.h"

using namespace std;

gameobject::gameobject(string object_name, int x, int y, int init_speed, double angle)
{
    xpos =x;
    ypos=y;
    direction = angle;
    speed = init_speed;
    name=object_name;

}

void gameobject::rotate(int turn_direction)
{
    direction = direction + 2*turn_direction;
}

void gameobject::move(double x_length, double y_length)
{
    xpos = xpos + speed*x_length;
    ypos = ypos + speed*y_length;
}
