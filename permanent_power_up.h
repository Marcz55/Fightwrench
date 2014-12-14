#ifndef PERMANENT_POWER_UP_H
#define PERMANENT_POWER_UP_H
#include "power_up.h"

class permanent_power_up : public power_up
{
public:
    permanent_power_up()=delete;
    permanent_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, double health);
};

#endif // PERMANENT_POWER_UP_H
