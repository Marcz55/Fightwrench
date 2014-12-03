#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include <string>
#include <math.h>

class character : public gameobject
{
    friend class input_handler;
public:
    character(int x_pos, int y_pos): gameobject("Axel", x_pos,y_pos){}

    void update() override;
    void update_move_vector();
    void ultimate(){};
protected:
    double x_movement = 0;
    double y_movement = 0;
    int up_key = 0;
    int down_key = 0;
    int left_key = 0;
    int right_key = 0;
    int turn_left_key = 0;
    int turn_right_key = 0;
    bool shoot_key = false;


};

#endif // CHARACTER_H
