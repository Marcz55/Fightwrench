#ifndef BOX_H
#define BOX_H
#include "cover.h"

class box : public cover
{
public:
    box(int init_x, int init_y, double angle, int health_input, double height_input, double width_input,class gamefield* init_gamefield):cover("box",init_x,init_y,angle,health_input,height_input,width_input,init_gamefield){}
};

#endif // BOX_H
