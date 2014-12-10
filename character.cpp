#include "character.h"
using namespace std;

character::character(string character_name, int x_pos, int y_pos, int speed, double angle,
                     string init_projectile, vector<projectile>* init_projectile_vector,
                     int init_firing_cooldown, soundhandler* init_soundhandler, int init_max_health,
                     int init_max_ammo, int init_reload_time): gameobject(character_name, x_pos,y_pos,speed,angle)
{
    projectile_type = init_projectile;
    projectile_vector = init_projectile_vector;
    firing_cooldown = init_firing_cooldown;
    main_soundhandler = init_soundhandler;
    current_health = init_max_health;
    max_ammo = init_max_ammo;
    current_ammo = init_max_ammo;
    reload_time = init_reload_time;
}

void character::update()
{
    if (reload_timer > 0)
    {
        if (reload_timer == 1)
        {
            reload_timer = 0;
            current_ammo = max_ammo;
        }
        else
        {
            reload_timer -= 1;
        }
    }
    this->rotate(turn_right_key - turn_left_key);
    this->move(x_movement,y_movement);
    if (firing_timer > 0)
    {
        firing_timer -= 1;
    }
    if (shoot_key && firing_timer <= 0 && current_ammo > 0)
    {
        this->fire_weapon();
        current_ammo -= 1;
        if (current_ammo <= 0)
        {
            reload_timer = reload_time;
        }
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
    if(temp_x !=0||temp_y != 0 )
    {
        if (temp_x == 0)
        {
            if (temp_y == 1)
            {
                movement_direction = 180;
            }
            else
            {
                movement_direction = 0;
            }
        }
        else if (temp_y == 0)
        {
            if (temp_x == 1)
            {
                movement_direction = 90;
            }
            else
            {
                movement_direction = 270;
            }
        }
        else
        {
            if (temp_x > 0 && temp_y > 0)
            {
                movement_direction = 135;
            }
            if (temp_x < 0 && temp_y > 0)
            {
                movement_direction = 225;
            }
            if (temp_x < 0 && temp_y < 0)
            {
                movement_direction = 315;
            }
            if (temp_x > 0 && temp_y < 0)
            {
                movement_direction = 45;
            }
        }
    }

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
        projectile_vector->push_back(bullet(xpos,ypos,direction - 90));
        firing_timer = firing_cooldown;
        main_soundhandler->play_sound("Gunshot"); //Denna rad gör att spelet krashar oftare än vad är lämpligt.
    }
    if(projectile_type == "grenade")
    {
        projectile_vector->push_back(grenade(xpos,ypos,direction - 90));
        firing_timer = firing_cooldown;
        main_soundhandler->play_sound("Gunshot"); //Denna rad gör att spelet krashar oftare än vad är lämpligt.
    }


}

