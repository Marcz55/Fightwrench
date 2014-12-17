#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include<string>
#include<vector>
#include "gameobject.h"
#include "character.h"
#include "cover.h"
#include "projectile.h"
#include "bullet.h"
#include "grenade.h"
#include "rocket.h"
#include "guided_rocket.h"
#include "power_up.h"

#include "explosion.h"

using namespace std;
class gamefield
{
public:
    gamefield() = default;
    gamefield(int win_height, int win_width, class soundhandler& init_soundhandler);
    void update();
    ~gamefield();
    gamefield(const gamefield&) = delete;
    gamefield& operator=(const gamefield&) = delete;
    void add_character(class character character_to_add);
    void add_projectile(string projectile_type, double projectile_x, double projectile_y,double projectile_x_movement,double projectile_y_movement, double projectile_angle, int damage, character* character_pointer);
    void add_cover(cover cover_to_add);
    void add_power_up(class power_up power_up_to_add);
    void add_explosion(double scale, double explosion_x, double explosion_y);
    vector<class character>* get_character_vector(){return &character_vector;}
    vector<cover>* get_cover_vector(){return &cover_vector;}
    vector<projectile>* get_projectile_vector(){return &projectile_vector;}
    vector<power_up>* get_power_up_vector(){return &power_up_vector;}
    vector<explosion>* get_explosion_vector(){return &explosion_vector;}
    int get_window_height(){return window_height;}
    int get_window_width(){return window_width;}
    void play_sound(const string sound_name);
    void check_powerups();
    bool allowed_to_move_rectangle(vector<double> rectangle_corners, character*);
    bool allowed_to_move_rectangle(vector<double> rectangle_corners, cover*);
    bool allowed_to_move_circle(double circle_x, double circle_y, int circle_radius);

    void send_disable_control();
    void send_command(int turn_direction);

private:
    soundhandler* main_soundhandler;
    int window_height = 900;
    int window_width = 1500;
    string map1;
    class collision_handler* collision_handler_pointer;
    vector<character> character_vector;
    vector<class projectile> projectile_vector;
    vector<class cover> cover_vector;
    vector<class power_up> power_up_vector;
    vector<explosion> explosion_vector;
};

#endif // GAMEFIELD_H
