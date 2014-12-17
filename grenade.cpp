#include "grenade.h"

using namespace std;


grenade::grenade(double init_x, double init_y,double init_x_movement,double init_y_movement, double angle,class gamefield *init_gamefield, int damage, class character* character_pointer):  projectile("grenade",init_x, init_y,init_x_movement,init_y_movement,10,angle,200,1,damage,init_gamefield,character_pointer)
{

}
