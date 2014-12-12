#include "game.h"
#include <time.h>
using namespace std;

game::game(soundhandler& main_soundhandler, int window_height, int window_width, const string Player1, const string Player2):main_gamefield {window_height, window_width}, main_graphic_engine{window_height, window_width}
{
    if(Player1 == "axel")
        main_gamefield.add_character(axel{700,500,30,main_gamefield.get_projectile_vector(),&main_soundhandler, main_gamefield.get_collision_handler_pointer()});
    if(Player1 == "marcus")
        main_gamefield.add_character(marcus{700,500,30,main_gamefield.get_projectile_vector(),&main_soundhandler, main_gamefield.get_collision_handler_pointer()});

    if(Player2 == "axel")
        main_gamefield.add_character(axel{700,500,30,main_gamefield.get_projectile_vector(),&main_soundhandler, main_gamefield.get_collision_handler_pointer()});
    if(Player2 == "marcus")
        main_gamefield.add_character(marcus{700,500,30,main_gamefield.get_projectile_vector(),&main_soundhandler, main_gamefield.get_collision_handler_pointer()});

    main_gamefield.add_cover(standardcover(300,300,0,10,30,150));

}

void game::main_update()
{
    main_graphic_engine.draw_all(main_gamefield);
    main_input_handler.update(main_gamefield);
    for(auto it = main_gamefield.get_character_vector()->begin(); it != main_gamefield.get_character_vector()->end(); it++)
    {
        it->update();
        it->update_move_vector(); //Denna bör läggas på lämplig plats i inputhanteraren.
    }
    for(auto it = main_gamefield.get_projectile_vector()->begin();/* (!main_gamefield.get_projectile_vector()->empty())&&*/(it != main_gamefield.get_projectile_vector()->end()); it++)
    {
        it->update();
        if(it->get_explosion_timer() == 0) //Fick oförklarade "pure virtual function called"-fel när vissa projectiler togs bort, undersök varför!
        {
            it += 1;
            if(it == main_gamefield.get_projectile_vector()->end())
            {
                it -= 1;
                main_gamefield.get_projectile_vector()->erase(it);
                break;
            }
            else
            {
                it -= 1;
                main_gamefield.get_projectile_vector()->erase(it);
            }
        }
    }

}

void game::game_loop()
{
    while(true)
    {
        clock_t elapsed_time = clock();
        this->main_update();
        elapsed_time = clock() - elapsed_time;
        if (elapsed_time < 10)
        {
            SDL_Delay(10-elapsed_time);
        }
    }
}
