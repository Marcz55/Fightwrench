#include "gamefield.h"

//Denna ska ta in argument och lägga till specifika objekt.
 void gamefield::add_object()
 {     
     character_vector.push_back(character(150, 300));
     character_vector.push_back(character(0, 0));
     character_vector.push_back(character(0, 100));
 }
