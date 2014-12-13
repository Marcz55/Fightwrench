#include "gamefield.h"
#include "power_up.h"

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

void gamefield::add_projectile(string projectile_type, double projectile_x, double projectile_y, double projectile_angle)
{
    if (projectile_type == "bullet")
    {
        projectile_vector.push_back(bullet(projectile_x,projectile_y,projectile_angle + 90,this));
        main_soundhandler->play_sound("Gunshot");
    }
    else if (projectile_type == "grenade")
    {
        projectile_vector.push_back(grenade(projectile_x,projectile_y,projectile_angle + 90,this));
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

collision_handler* gamefield::get_collision_handler_pointer()
{
    return collision_handler_pointer;
}



void gamefield::play_sound(const string sound_name)
{
    main_soundhandler->play_sound(sound_name);
}

