#include "game.h"
#include <time.h>

using namespace std;

game::game()
{
}

void game::main_update()
{
    main_graphic_engine.draw_all(main_gamefield);
    main_input_handler.update(main_gamefield);
    for(auto it = main_gamefield.get_character_vector.begin(); it != main_gamefield.get_character_vector.end(); it++)
    {
        it->update();
        it->update_movement_vector(); //Denna bör läggas på lämplig plats i inputhanteraren.
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
