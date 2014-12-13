#include "power_up.h"

power_up::power_up(std::string name1, int x, int y, double angle, int input_radius, int input_duration, gamefield *init_gamefield):gameobject(name1, x, y,0,angle, init_gamefield)
{
    radius = input_radius;
    duration=input_duration;
}
bool power_up::check_pick_up_status()
{
    return is_picked_up;
}
