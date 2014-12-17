
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
class gameobject
{
public:
    gameobject(std::string object_name,int x, int y, int init_speed, double angle, class gamefield* init_gamefield);
    virtual void update() = 0;
    virtual ~gameobject() =default;
    gameobject(const gameobject&) = default;
    gameobject(gameobject&&) = default;
    gameobject& operator=(const gameobject&) = default;
    gameobject& operator=(gameobject&&) = default;
    //virtual void move(double x_length, double y_length);
    //virtual void rotate(int turn_direction); //turn_direction är 0 eller +-1 för att avgöra om
                                             //objektet ska vridas och åt vilket håll.
    virtual std::string get_name()const {return name;}
    virtual double get_xpos()const {return xpos;}
    virtual double get_ypos()const{return ypos;}
    virtual double get_direction()const{return direction;}
    virtual double get_speed()const{return direction;}
    virtual double get_forced_x_movement()const{return forced_x_movement;}
    virtual double get_forced_y_movement()const{return forced_y_movement;}
    virtual void set_forced_x_movement(double value){forced_x_movement = value;}
    virtual void set_forced_y_movement(double value){forced_y_movement = value;}
protected:
    class gamefield* main_gamefield;
    std::string name;
    double xpos;
    double ypos;
    double direction;
    double speed;
    double forced_x_movement = 0;
    double forced_y_movement = 0;



};

#endif // GAMEOBJECT_H
