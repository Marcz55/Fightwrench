#ifndef COVER_H
#define COVER_H
#include "gameobject.h"
class cover : public gameobject
{
public:
    cover(std::string name1, int x, int y, double angle, int health_input, int height_input, int width_input);
    cover()=delete;
    ~cover()=default;


    //getters
    int get_health(){return health;}
    int get_height(){return height;}
    int get_width(){return width;}

    //setters
    void set_health(int new_health);
    void set_height(int new_height);
    void set_width(int new_width);




private:
    int health = 0;
    int height = 0;
    int width = 0;
};

#endif // COVER_H
