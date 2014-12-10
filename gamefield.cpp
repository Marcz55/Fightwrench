#include "gamefield.h"

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
