#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include <vector>
#include "character.h"
#include "cover.h"
#include "gamefield.h"
#include <cmath>
#include "gamefield.h"
#include <iterator>
using namespace std;

class collision_handler
{
public:
    collision_handler(class gamefield*);
    ~collision_handler() = default;
    bool allowed_to_move_rectangle(vector<double>);
    bool allowed_to_move_circle(double,double,int);


private:
    class gamefield* gamefield_pointer;
    //vector<cover>* cover_vector_pointer;
    int window_height;
    int window_width;

};

#endif // COLLISION_HANDLER_H
