#include "gameobject.h"

using namespace std;

gameobject::gameobject(string object_name, int x, int y, int init_speed, double angle,class gamefield *init_gamefield)
{
    xpos =x;
    ypos=y;
    direction = angle;
    speed = init_speed;
    name=object_name;
    main_gamefield = init_gamefield;


}

/*void gameobject::rotate(int turn_direction)
{
    direction = direction + 2*turn_direction;

    //För stora/små vinklar leder till konstigheter, bägransar intervall till [0,360]
    if (direction > 360)
    {
        direction = direction - 360;
    }
    if (direction < 0)
    {
        direction = direction + 360;
    }
}

void gameobject::move(double x_length, double y_length)
{

    xpos = xpos + speed*x_length;
    ypos = ypos + speed*y_length;
}*/
