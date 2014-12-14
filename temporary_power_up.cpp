#include "temporary_power_up.h"

temporary_power_up::temporary_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, double dmg, double health,double fire_speed, double move_speed, int input_duration):power_up(name1,x, y, angle, input_radius, init_gamefield, dmg, health,fire_speed, move_speed,input_duration)
{
    is_permanent=false;
}

