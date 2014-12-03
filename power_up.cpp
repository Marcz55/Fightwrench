#include "power_up.h"

power_up::power_up(std::string name1, int x, int y, int input_radius, int input_duration):gameobject(name1, x, y)
{
    radius = input_radius;
    duration=input_duration;
}
bool power_up::check_pick_up_status()
{
    return is_picked_up;
}

