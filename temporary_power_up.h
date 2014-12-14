#ifndef TEMPORARY_POWER_UP_H
#define TEMPORARY_POWER_UP_H
#include "power_up.h"

class temporary_power_up : public power_up
{
public:
    temporary_power_up()=delete;
    temporary_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, double dmg, double health,double fire_speed, double move_speed, int input_duration);
    int get_duration(){return duration;}
};

#endif // TEMPORARY_POWER_UP_H
