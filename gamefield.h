#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include<string>
#include<vector>
#include "gameobject.h"
#include "character.h"

using namespace std;
class gamefield
{
    friend class collision_handler;
    friend class graphic_engine;
public:
    gamefield() = default;
    gamefield(string map, string character_one, string character_two);
    void update();
    ~gamefield()=default;
    void add_object();


private:
    int window_height = 600;
    int window_width = 800;
    string map1;
    vector<class character> character_vector;
    vector<class projectile> projectile_vector;
    vector<class cover> cover_vector;
    vector<class power_up> power_up_vector;
};

#endif // GAMEFIELD_H
