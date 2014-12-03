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
