#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include <vector>
#include "character.h"
#include "cover.h"
#include "gamefield.h"
#include "array"
#include <cmath>
#include "gamefield.h"
#include <iterator>
class collision_handler
{
public:
    collision_handler(gamefield*);
    ~collision_handler() = default;
    bool allowed_to_move_rectangle(double,double,double,double,double,double,double,double);
    //bool allowed_to_move_circle(int,int,int);


private:
    gamefield* gamefield_pointer;
    //vector<cover>* cover_vector_pointer;
  };

#endif // COLLISION_HANDLER_H
