#include "power_up.h"

power_up::power_up(std::string name1, int x, int y, double angle, int input_radius, gamefield *init_gamefield, double dmg, double health,double fire_speed, double move_speed, int init_duration):gameobject(name1, x, y,0,angle, init_gamefield)
{
    radius = input_radius;
    delta_health=health;
    delta_damage = dmg;
    delta_fire_speed = fire_speed;
    delta_move_speed  = move_speed;
    duration = init_duration;
}
