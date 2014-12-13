#include "temporary_power_up.h"

temporary_power_up::temporary_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, int dmg, int health, int input_duration):power_up(name1,x, y, angle, input_radius, init_gamefield, dmg, health)
{
    duration=input_duration;
}

