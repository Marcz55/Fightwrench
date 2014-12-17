#include "game.h"
#include <time.h>
#include <iostream>
using namespace std;

game::game(soundhandler& main_soundhandler, int window_height, int window_width, const string Player1, const string Player2,const int window_height_scale,const int window_width_scale):main_gamefield {window_height, window_width,main_soundhandler}, main_graphic_engine{window_height, window_width,window_height_scale,window_width_scale}
{
    if(Player1 == "axel")//Namnet som settas här MÅSTE vara samma sak som motsvarande textur i graphic engine.
        main_gamefield.add_character(axel{100,100,0,&main_gamefield});
    if(Player1 == "marcus")
        main_gamefield.add_character(marcus{100,100,0,&main_gamefield});
    if(Player1 == "nasse")
        main_gamefield.add_character(nasse{100,100,315,&main_gamefield});

    if(Player2 == "axel")
        main_gamefield.add_character(axel{1400,700,90,&main_gamefield});
    if(Player2 == "marcus")
        main_gamefield.add_character(marcus{1400,700,90,&main_gamefield});
    if(Player2 == "nasse")
        main_gamefield.add_character(nasse{1400,700,135,&main_gamefield});
    running = true;
    secondmap();

}

void game::firstmap()
{
    main_gamefield.add_cover(standardcover(300,300,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(450,300,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(600,300,0,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(450,210,90,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(210,360,90,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(210,510,90,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(440,610,90,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(500,700,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(650,700,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(800,700,0,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(700,500,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(850,500,0,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(1050,450,90,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(1050,300,90,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(1000,180,45,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(1100,180,135,10,30,80,&main_gamefield));

    main_gamefield.add_cover(standardcover(1425,300,0,10,30,80,&main_gamefield));
    main_gamefield.add_cover(standardcover(1335,360,90,10,30,80,&main_gamefield));



}

void game::secondmap()
{
    for(int cov_it = 0; cov_it <= 16; cov_it ++)
    {
        main_gamefield.add_cover(standardcover(200 + cov_it*81,150,0,10,30,80,&main_gamefield));
        main_gamefield.add_cover(standardcover(40 + cov_it*81,650,0,10,30,80,&main_gamefield));
    }
    for(int cov_it = 0; cov_it <= 3; cov_it ++)
    {
        main_gamefield.add_cover(standardcover(175,205 + cov_it*81,90,10,30,80,&main_gamefield));
        main_gamefield.add_cover(standardcover(1345,595 - cov_it*81,90,10,30,80,&main_gamefield));
    }

     main_gamefield.add_cover(box(700,350,0,10,90,90,&main_gamefield));
     main_gamefield.add_cover(box(700,450,0,10,90,90,&main_gamefield));
     main_gamefield.add_cover(box(800,400,0,10,90,90,&main_gamefield));
     main_gamefield.add_cover(box(300,300,0,10,90,90,&main_gamefield));
     main_gamefield.add_cover(box(900,250,0,10,90,90,&main_gamefield));

     main_gamefield.add_cover(box(1290,500,0,10,90,90,&main_gamefield));
     main_gamefield.add_cover(box(1250,300,0,10,90,90,&main_gamefield));
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
    power_up_spawn_timer -= 1;
    if(power_up_spawn_timer <= 0)
    {
        spawn_powerup();
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
        /* Koden nedan, fram till markering är skriven av Markus Petersson och hanterar vad som händer då en spelare vinner.*/
        while(main_gamefield.get_character_vector()->at(0).get_health()<=0)
        {
            main_graphic_engine.display_winner(main_gamefield.get_character_vector()->at(1).get_portrait_name());

            SDL_Delay(2000);
            while (SDL_PollEvent(&event))	{
                if ( event.type == SDL_KEYDOWN )	{
                    return;
                }
            }

        }
        while(main_gamefield.get_character_vector()->at(1).get_health()<=0)
        {

            main_graphic_engine.display_winner(main_gamefield.get_character_vector()->at(0).get_portrait_name());

            SDL_Delay(2000);
            while (SDL_PollEvent(&event))	{
                if ( event.type == SDL_KEYDOWN )	{
                    return;
                }
            }

        }
        /* Markering*/

    }
    return;
}

void game::spawn_powerup()
{
    srand (time(NULL));
    int spawn_randomizer = rand() % 5 + 1;
    double xpos_randomizer = rand() % 1300 + 100;
    double ypos_randomizer = rand() % 600 + 100;
    //Denna helar permanent
    if(spawn_randomizer == 1)
    {
        main_gamefield.add_power_up(permanent_power_up("life", xpos_randomizer, ypos_randomizer, 0, 25, &main_gamefield,25));
    }


    //Denna ger temporär ökning i liv
    if(spawn_randomizer == 2)
    {
        main_gamefield.add_power_up(temporary_power_up("steroids", xpos_randomizer, ypos_randomizer, 0, 25, &main_gamefield, 1, 2,1,1,1000));
        cout << "temp liv" << endl;
    }


    //Denna ger temporär ökning i skada
    if(spawn_randomizer == 3)
    {
        main_gamefield.add_power_up(temporary_power_up("damage_buff", xpos_randomizer, ypos_randomizer, 0, 25, &main_gamefield, 2, 1,1,1,1000));
        cout << "temp skada" << endl;
    }



    //Denna ger temporär ökning i eldhastighet
    if(spawn_randomizer == 4)
    {
        main_gamefield.add_power_up(temporary_power_up("firing_speed_buff", xpos_randomizer, ypos_randomizer, 0, 25, &main_gamefield, 1, 1,0.5,1,1000));
        cout << "temp eldhast" << endl;
    }


    //Denna ger temporär ökning i rörelsehastighet
    if(spawn_randomizer == 5)
    {
        main_gamefield.add_power_up(temporary_power_up("speed_buff", xpos_randomizer, ypos_randomizer, 0, 25, &main_gamefield, 1, 1,1,2,1000));
        cout << "temp rörhast" << endl;
    }




    power_up_spawn_timer = 1000 + (rand() % 1000);
}
