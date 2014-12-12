#include "gamefield.h"
#include "power_up.h"
gamefield::~gamefield()
{
    delete collision_handler_pointer;
    collision_handler_pointer = nullptr;

}

gamefield::gamefield(int win_height, int win_width)
{
    window_height = win_height;
    window_width = win_width;
    collision_handler_pointer = new class collision_handler(this);
}

//Denna ska ta in argument och lägga till specifika objekt.
 void gamefield::add_character(character character_to_add)
 {     
     character_vector.push_back(character_to_add);
 }

 void gamefield::add_projectile(projectile projectile_to_add)
 {
     projectile_vector.push_back(projectile_to_add);
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

