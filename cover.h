#ifndef COVER_H
#define COVER_H
#include "gameobject.h"
#include <vector>
#include <cmath>
using namespace std;
class cover : public gameobject
{
public:
    cover(std::string name1, int x, int y, double angle, int health_input, double height_input, double width_input,class gamefield* init_gamefield);
    cover()=delete;
    cover(const cover&) = default;
    cover& operator=(const cover&) = default;
    virtual ~cover() override =default;
    void update() override;
    cover* get_pointer_to_yourself(){return this;}

    vector<double> get_corners();

    //getters
    int get_health(){return health;}
    double get_height(){return height;}
    double get_width(){return width;}

    //setters
    void set_health(int new_health);
    void set_height(int new_height);
    void set_width(int new_width);




protected:
    int health = 0;
    double height = 0;
    double width = 0;
};

#endif // COVER_H
