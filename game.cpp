#include "game.h"

using namespace std;

game::game()
{
}

void game::main_update()
{
    main_graphic_engine.draw_all(g1);
    main_input_handler.update(g1);
}

void game::game_loop
{
    while(true)
    {
        this->main_update()

    }
}
