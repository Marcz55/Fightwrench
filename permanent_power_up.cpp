#include "permanent_power_up.h"

permanent_power_up::permanent_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, double health):power_up(name1,x, y, angle, input_radius, init_gamefield, 1, health,1,1,1)
{
    is_permanent = true;
}

