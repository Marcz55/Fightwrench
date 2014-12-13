#include "grenade.h"

using namespace std;

grenade::grenade(double init_x, double init_y, double angle,class gamefield *init_gamefield):projectile("grenade",init_x, init_y,10,angle,200,100,15,init_gamefield)
{

}
