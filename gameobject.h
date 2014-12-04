#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>

class gameobject
{
public:
    gameobject(std::string object_name,int x, int y, int init_speed, double angle);
    virtual void update() = 0;
    virtual void move(double x_length, double y_length);
    virtual void rotate(int turn_direction); //turn_direction är 0 eller +-1 för att avgöra om
                                             //objektet ska vridas och åt vilket håll.
    virtual std::string get_name(){return name;}
    virtual int get_xpos(){return xpos;}
    virtual int get_ypos(){return ypos;}
    virtual double get_direction(){return direction;}

protected:
    std::string name;
    double xpos;
    double ypos;
    double direction;
    double speed;



};

#endif // GAMEOBJECT_H
