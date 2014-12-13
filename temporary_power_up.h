#ifndef TEMPORARY_POWER_UP_H
#define TEMPORARY_POWER_UP_H
#include "power_up.h"

class temporary_power_up : public power_up
{
public:
    temporary_power_up()=delete;
    temporary_power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, int dmg, int health, int input_duration);
    int get_duration(){return duration;}
private:
    int duration;
};

#endif // TEMPORARY_POWER_UP_H
