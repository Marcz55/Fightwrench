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
    running = true;

}

void game::main_update()
{
    main_graphic_engine.draw_all(main_gamefield);
    main_input_handler.update(main_gamefield);
    running = main_input_handler.Get_running();
    for(auto it = main_gamefield.get_character_vector()->begin(); it != main_gamefield.get_character_vector()->end(); it++)
    {
        it->update();
        it->update_move_vector(); //Denna bör läggas på lämplig plats i inputhanteraren.
    }
    for(auto it = main_gamefield.get_projectile_vector()->begin(); it != main_gamefield.get_projectile_vector()->end(); it++)
    {
        it->update();
    }

}

void game::game_loop()
{
    while(running)
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
