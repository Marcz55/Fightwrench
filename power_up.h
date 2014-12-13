#ifndef POWER_UP_H
#define POWER_UP_H
#include "gameobject.h"
#include "character.h"

class power_up : public gameobject
{
public:
    power_up()=delete;
    power_up(std::string name1, int x, int y,double angle, int input_radius,class gamefield* init_gamefield, int dmg, int health);
    ~power_up()=default;
    virtual void update() override{}
    //power_up(power_up& copy_power_up)=default;
    bool check_pick_up_status();
  //  void pick_up(character& up_picker);
    virtual int get_delta_health(){return delta_health;}
    virtual int get_delta_damage(){return delta_damage;}
private:
    int radius;
    int delta_health;
    int delta_damage;
    bool is_picked_up = false; //

};

#endif // POWER_UP_H
