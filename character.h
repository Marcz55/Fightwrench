#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include "projectile.h"
#include "bullet.h"
#include "grenade.h"
#include "soundhandler.h"
#include <string>
#include <math.h>
#include <vector>

class character : public gameobject
{
    //friend class input_handler;
public:
    character(std::string character_name,int x_pos, int y_pos, int speed, double angle, std::string init_projectile, std::vector<projectile>* init_projectile_vector,int init_firing_cooldown, soundhandler* init_soundhandler);

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
    int get_movement_direction(){return movement_direction;}
    void fire_weapon();

protected:
    double x_movement = 0;
    double y_movement = 0;
    int up_key = 0;
    int down_key = 0;
    int left_key = 0;
    int right_key = 0;
    int turn_left_key = 0;
    int turn_right_key = 0;
    double movement_direction = 0;
    bool shoot_key = false;
    int firing_cooldown; //Antal tic en karaktär måste vänta innan den kan skjuta igen.
    int firing_timer = 0;    //Den timer som räknas ner och sätt till firing_cooldown när man skjuter.
    std::string projectile_type;
    std::vector<projectile>* projectile_vector;
    soundhandler* main_soundhandler;



};

#endif // CHARACTER_H
