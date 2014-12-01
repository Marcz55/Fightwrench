#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include <string>

class character : public gameobject
{
public:
    character(int x_pos, int y_pos): gameobject(x_pos,y_pos){}

    void update() override;
    std::string get_name(){return name;}
    int get_xpos(){return xpos;}
    int get_ypos(){return ypos;}
    double get_direction(){return direction;}



};

#endif // CHARACTER_H
