#include "bullet.h"

void bullet::update()
{
    xpos = xpos + x_movement;
    ypos = ypos + y_movement;
}
