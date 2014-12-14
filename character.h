#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"
#include "projectile.h"
#include "bullet.h"
#include "grenade.h"
#include "soundhandler.h"
#include <string>
#include <math.h>
#include <vector>
#include "power_up.h"
#include <collision_handler.h>
class character : public gameobject
{
public:
    character(std::string character_name, int x_pos, int y_pos, int speed, double angle,
              std::string init_projectile,
              int init_firing_cooldown,int init_max_health,
              int init_max_ammo, int init_reload_time, double width, double height, class collision_handler* init_collision_handler, std::string port_name = "", class gamefield* init_gamefield = nullptr, int init_damage=0);

    void update() override;
    void update_move_vector();
    void ultimate() {}
    void input_set_up(const int);
    void input_set_down(const int);
    void input_set_left(const int);
    void input_set_right(const int);
    void input_set_turn_left(const int);
    void input_set_turn_right(const int);
    void input_set_shoot(const bool);
    int get_up_key()
    {
        return up_key;
    }
    int get_movement_direction()
    {
        return movement_direction;
    }
    int get_health()
    {
        return current_health;
    }
    double get_health_percent()
    {
        return ((double)current_health) / ((double)max_health);
    }
    double get_ammo_percent()
    {
        return ((double)current_ammo) / ((double)max_ammo);
    }
    double get_reload_percent()
    {
        return ((double)reload_timer) / ((double)reload_time);
    }
    std::string get_portrait_name()
    {
        return portrait_name;
    }

    void fire_weapon();
    std::vector<double> get_corners();
    void move(double x_length, double y_length,int turn_direction);
    virtual void pick_up_power_up(const power_up& po_up);
    virtual void set_health(int new_health){current_health=new_health;}



protected:
    double x_movement = 0;
    double y_movement = 0;
    int up_key = 0;
    int down_key = 0;
    int left_key = 0;
    int right_key = 0;

    int turn_left_key = 0;
    int turn_right_key = 0;
    int current_health = 0;
    int max_health = 0;
    int current_ammo = 0;
    int max_ammo = 0;
    int reload_time = 0;
    int damage = 0;

    int reload_timer = 0;
    double movement_direction = 0;
    bool shoot_key = false;
    int firing_cooldown; //Antal tic en karaktär måste vänta innan den kan skjuta igen.
    int firing_timer = 0;    //Den timer som räknas ner och sätt till firing_cooldown när man skjuter.
    std::string projectile_type;
    //soundhandler* main_soundhandler;
    class collision_handler* gamefield_collision_handler;
    double width = 0;
    double height = 0;
    std::string portrait_name;
    std::vector<class power_up> active_power_ups;


};

#endif // CHARACTER_H
