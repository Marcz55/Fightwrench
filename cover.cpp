#include "cover.h"

cover::cover(std::string name1, int x, int y, int health_input, int height_input, int width_input):gameobject(name1, x, y)
{
    health=health_input;
    width=width_input;
    height=height_input;
}
void cover::set_health(int new_health)
{
    health=new_health;
}

void cover::set_height(int new_height)
{
    height=new_height;
}

void cover::set_width(int new_width)
{
    width=new_width;
}
