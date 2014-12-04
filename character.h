#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include <string>
#include <math.h>

class character : public gameobject
{
    //friend class input_handler;
public:
    character(std::string character_name,int x_pos, int y_pos, int speed, double angle): gameobject(character_name, x_pos,y_pos,speed,angle){}

    void update() override;
    void update_move_vector();
    void ultimate(){};
    void input_set_up(const int);
    void input_set_down(const int);
    void input_set_left(const int);
    void input_set_right(const int);
    void input_set_turn_left(const int);
    void input_set_turn_right(const int);
    void input_set_shoot(const bool);
    int get_up_key(){return up_key;}
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
