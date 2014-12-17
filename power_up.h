#ifndef POWER_UP_H
#define POWER_UP_H
#include "gameobject.h"
#include "character.h"

class power_up : public gameobject
{
public:
    power_up()=delete;
    power_up(std::string name1, int x, int y,double angle, int input_radius,class gamefield* init_gamefield, double dmg, double health,double fire_speed, double move_speed,int init_duration);
    virtual ~power_up() override = default;
    power_up(const power_up&) = default;
    power_up(power_up&&) = default;
    power_up& operator=(const power_up&) = default;
    power_up& operator=(power_up&&) = default;
    virtual void update() override{duration=duration-1;}
    //power_up(power_up& copy_power_up)=default;

  //  void pick_up(character& up_picker);
    virtual double get_delta_health()const{return delta_health;}
    virtual double get_delta_damage()const{return delta_damage;}
    virtual double get_delta_fire_speed()const{return delta_fire_speed;}
    virtual double get_delta_move_speed()const{return delta_move_speed;}
    virtual bool get_type()const{return is_permanent;}
    virtual int get_duration()const{return duration;}
    virtual int get_radius()const{return radius;}
protected:
    int radius;
    double delta_health;
    double delta_damage;
    double delta_fire_speed;
    double delta_move_speed;
    bool is_permanent = false; //
    int duration;

};

#endif // POWER_UP_H
