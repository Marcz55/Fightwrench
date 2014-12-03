#include "gameobject.h"

using namespace std;

gameobject::gameobject(string name1, int x, int y)
{
    xpos =x;
    ypos=y;
    direction = 0;
    speed = 10;
    name=name1;

}

void gameobject::rotate(int turn_direction)
{
    direction = direction + turn_direction;
}

void gameobject::move(double x_length, double y_length)
{
    xpos = xpos + speed*x_length;
    ypos = ypos + speed*y_length;
}
