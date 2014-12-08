#ifndef COVER_H
#define COVER_H
#include "gameobject.h"
#include <vector>
#include <cmath>
using namespace std;
class cover : public gameobject
{
public:
    cover(std::string name1, int x, int y, double angle, int health_input, double height_input, double width_input);
    cover()=delete;
    ~cover()=default;

    vector<double> get_corners();

    //getters
    int get_health(){return health;}
    double get_height(){return height;}
    double get_width(){return width;}

    //setters
    void set_health(int new_health);
    void set_height(int new_height);
    void set_width(int new_width);




private:
    int health = 0;
    double height = 0;
    double width = 0;
};

#endif // COVER_H
