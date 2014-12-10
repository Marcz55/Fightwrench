#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include<string>
#include<vector>
#include "gameobject.h"
#include "character.h"
#include "cover.h"
#include "projectile.h"

using namespace std;
class gamefield
{
    friend class graphic_engine;
public:
    gamefield() = default;
    gamefield(int win_height, int win_width):window_height{win_height}, window_width{win_width}{}
    gamefield(string map, string character_one, string character_two);
    void update();
    ~gamefield()=default;
    void add_character(character character_to_add);
    void add_projectile(projectile projectile_to_add);
    void add_cover(cover cover_to_add);
    vector<character>* get_character_vector(){return &character_vector;}
    vector<cover>* get_cover_vector(){return &cover_vector;}
    vector<projectile>* get_projectile_vector(){return &projectile_vector;}
    int get_window_height(){return window_height;}
    int get_window_width(){return window_width;}

private:
    int window_height = 600;
    int window_width = 800;
    string map1;
    vector<character> character_vector;
    vector<class projectile> projectile_vector;
    vector<class cover> cover_vector;
   // vector<class power_up> power_up_vector;
};

#endif // GAMEFIELD_H
