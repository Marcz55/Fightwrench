#include "gamefield.h"
#include "power_up.h"
#include "collision_handler.h"

using namespace std;

gamefield::~gamefield()
{
    delete collision_handler_pointer;
    collision_handler_pointer = nullptr;

}

gamefield::gamefield(int win_height, int win_width,class soundhandler &init_soundhandler)
{
    window_height = win_height;
    window_width = win_width;
    collision_handler_pointer = new class collision_handler(this);
    main_soundhandler = &init_soundhandler;
}

//Denna ska ta in argument och lägga till specifika objekt.
void gamefield::add_character(character character_to_add)
{
    character_vector.push_back(character_to_add);
}

void gamefield::add_projectile(string projectile_type, double projectile_x, double projectile_y, double projectile_angle, int damage)
{
    if (projectile_type == "bullet")
    {
        projectile_vector.push_back(bullet(projectile_x,projectile_y,projectile_angle + 90,this, damage));
        main_soundhandler->play_sound("Gunshot");
    }
    else if (projectile_type == "grenade")
    {
        projectile_vector.push_back(grenade(projectile_x,projectile_y,projectile_angle + 90,this,damage));
        main_soundhandler->play_sound("Gunshot");
    }

}

void gamefield::add_cover(cover cover_to_add)
{
    cover_vector.push_back(cover_to_add);
}
void gamefield::add_power_up(power_up power_up_to_add)
{
    power_up_vector.push_back(power_up_to_add);
}

void gamefield::add_explosion(double scale, double explosion_x, double explosion_y)
{
    explosion_vector.push_back(explosion(scale,explosion_x,explosion_y,this));
}


void gamefield::play_sound(const string sound_name)
{
    main_soundhandler->play_sound(sound_name);
}

void gamefield::update()
{
    check_powerups();
    for(auto it = explosion_vector.begin(); it != explosion_vector.end(); it++)
    {
        it->update();
        if(it->get_timer() == 0)
        {
            it += 1;
            if (it == explosion_vector.end())
            {
                it -=1;
                explosion_vector.erase(it);
                break;
            }
            else
            {
                it -=1;
                explosion_vector.erase(it);
            }
        }
    }

    for(auto it = projectile_vector.begin(); it != projectile_vector.end(); it++)
    {
        it->update();
        if(it->get_explosion_timer() == 0)
        {
            add_explosion(0.5,it->get_xpos(),it->get_ypos());
            main_soundhandler->play_sound("Explosion");
            it += 1;
            if (it == projectile_vector.end())
            {
                it -=1;
                projectile_vector.erase(it);
                break;
            }
            else
            {
                it -=1;
                projectile_vector.erase(it);
            }
        }
    }
}

void gamefield::check_powerups()
{
    for(auto itchar = character_vector.begin(); itchar != character_vector.end(); itchar ++)
    {
        for(auto itpow = power_up_vector.begin(); itpow != power_up_vector.end(); itpow ++)
        {
            double distance_sqrd = pow(itchar->get_xpos() - itpow->get_xpos(),2) + pow(itchar->get_ypos() - itpow->get_ypos(),2);
            if(distance_sqrd <= pow(itpow->get_radius(),2))
            {
                itchar->pick_up_power_up(*itpow);
                power_up_vector.erase(itpow--);
            }
        }
    }
}

bool gamefield::allowed_to_move_rectangle(vector<double> rectangle_corners)
{
    return collision_handler_pointer->allowed_to_move_rectangle(rectangle_corners);
}

bool gamefield::allowed_to_move_circle(double circle_x, double circle_y, int circle_radius)
{
    return collision_handler_pointer->allowed_to_move_circle(circle_x,circle_y,circle_radius);
}

