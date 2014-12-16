#include "grenade.h"

using namespace std;

grenade::grenade(double init_x, double init_y, double angle,class gamefield *init_gamefield, int damage, class character* character_pointer):  projectile("grenade",init_x, init_y,10,angle,200,100,damage,init_gamefield,character_pointer)
{

}
