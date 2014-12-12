#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include<string>
#include<vector>
#include "gameobject.h"
#include "character.h"
#include "cover.h"
#include "projectile.h"
#include "collision_handler.h"

using namespace std;
class gamefield
{
    friend class graphic_engine;
public:
    gamefield() = default;
    gamefield(int win_height, int win_width);
    void update();
    ~gamefield();
    void add_character(class character character_to_add);
    void add_projectile(projectile projectile_to_add);
    void add_cover(cover cover_to_add);
    vector<class character>* get_character_vector(){return &character_vector;}
    vector<cover>* get_cover_vector(){return &cover_vector;}
    vector<projectile>* get_projectile_vector(){return &projectile_vector;}
    int get_window_height(){return window_height;}
    int get_window_width(){return window_width;}
    class collision_handler* get_collision_handler_pointer();

private:
    int window_height = 900;
    int window_width = 1500;
    string map1;
    class collision_handler* collision_handler_pointer;
    vector<character> character_vector;
    vector<class projectile> projectile_vector;
    vector<class cover> cover_vector;
   // vector<class power_up> power_up_vector;
};

#endif // GAMEFIELD_H
