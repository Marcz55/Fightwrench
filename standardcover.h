#ifndef STANDARDCOVER_H
#define STANDARDCOVER_H
#include "cover.h"

class standardcover : public cover
{
public:
    standardcover(int init_x, int init_y, double angle, int health_input, double height_input, double width_input):cover("standardcover",init_x,init_y,angle,health_input,height_input,width_input){}
};

#endif // STANDARDCOVER_H
