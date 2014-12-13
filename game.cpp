#include "game.h"
#include <time.h>
using namespace std;

game::game(soundhandler& main_soundhandler, int window_height, int window_width, const string Player1, const string Player2):main_gamefield {window_height, window_width,main_soundhandler}, main_graphic_engine{window_height, window_width}
{
    if(Player1 == "axel")//Namnet som settas här MÅSTE vara samma sak som motsvarande textur i graphic engine.
        main_gamefield.add_character(axel{100,100,315,main_gamefield.get_collision_handler_pointer(),&main_gamefield});
    if(Player1 == "marcus")
        main_gamefield.add_character(marcus{100,100,315,main_gamefield.get_collision_handler_pointer(),&main_gamefield});

    if(Player2 == "axel")
        main_gamefield.add_character(axel{1400,700,135,main_gamefield.get_collision_handler_pointer(),&main_gamefield});
    if(Player2 == "marcus")
        main_gamefield.add_character(marcus{1400,700,135,main_gamefield.get_collision_handler_pointer(),&main_gamefield});
    main_gamefield.add_power_up(power_up("power_up",600,600,0,0,&main_gamefield, 0, 0));
    running = true;
    firstmap();

}

void game::firstmap()
{
    main_gamefield.add_cover(standardcover(300,300,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(450,300,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(600,300,0,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(450,210,90,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(210,360,90,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(210,510,90,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(440,610,90,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(500,700,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(650,700,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(800,700,0,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(700,500,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(850,500,0,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(1050,450,90,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(1050,300,90,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(1000,180,45,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(1100,180,135,10,30,150,&main_gamefield));

    main_gamefield.add_cover(standardcover(1425,300,0,10,30,150,&main_gamefield));
    main_gamefield.add_cover(standardcover(1335,360,90,10,30,150,&main_gamefield));



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
    main_gamefield.update();

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
