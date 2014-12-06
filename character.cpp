#include "character.h"
using namespace std;

character::character(string character_name,int x_pos, int y_pos, int speed, double angle, string init_projectile, vector<projectile>* init_projectile_vector,int init_firing_cooldown, soundhandler* init_soundhandler): gameobject(character_name, x_pos,y_pos,speed,angle)
{
    projectile_type = init_projectile;
    projectile_vector = init_projectile_vector;
    firing_cooldown = init_firing_cooldown;
    main_soundhandler = init_soundhandler;
}

void character::update()
{
    this->rotate(turn_right_key - turn_left_key);
    this->move(x_movement,y_movement);
    if (firing_timer > 0)
    {
        firing_timer -= 1;
    }
    if (shoot_key && firing_timer <= 0)
    {
        this->fire_weapon();
    }


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

void character::fire_weapon()
{
    if(projectile_type == "bullet")
    {
        projectile_vector->push_back(bullet(xpos,ypos,direction));
        firing_timer = firing_cooldown;
        main_soundhandler->play_sound("Gunshot"); //Denna rad gör att spelet krashar oftare än vad är lämpligt.
    }
    if(projectile_type == "grenade")
    {
        projectile_vector->push_back(grenade(xpos,ypos,direction));
        firing_timer = firing_cooldown;
        main_soundhandler->play_sound("Gunshot"); //Denna rad gör att spelet krashar oftare än vad är lämpligt.
    }


}
