#include "power_up.h"

power_up::power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, int dmg, int health):gameobject(name1, x, y,0,angle, init_gamefield)
{
    radius = input_radius;
    delta_health=health;
    delta_damage = dmg;
}
