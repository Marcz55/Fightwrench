#include "character.h"
using namespace std;
void character::update()
{
    this->rotate(turn_right_key - turn_left_key);
    this->move(x_movement,y_movement);
}

void character::update_move_vector()
{
    double temp_x = right_key - left_key;
    double temp_y = down_key - up_key;
    if(temp_x !=0||temp_y != 0 )
    {
        x_movement = temp_x/sqrt(temp_x*temp_x + temp_y*temp_y);
        y_movement = temp_y/sqrt(temp_x*temp_x + temp_y*temp_y);
    }
    else
    {
        y_movement = 0;
        x_movement = 0;
    };
}
void character::input_set_up(const int up)
{
    up_key = up;
}

void character::input_set_down(const int down)
{
    down_key = down;
}

void character::input_set_left(const int left)
{
    left_key = left;
}

void character::input_set_right(const int right)
{
    right_key = right;
}

void character::input_set_turn_left(const int turn_left)
{
    turn_left_key = turn_left;
}

void character::input_set_turn_right(const int turn_right)
{
    turn_right_key = turn_right;
}

void character::input_set_shoot(const bool shoot)
{
    shoot_key = shoot;
}
