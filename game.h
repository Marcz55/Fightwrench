#ifndef GAME_H
#define GAME_H
#include "gamefield.h"
#include "graphic_engine.h"
#include "input_handler.h"


class game
{
public:
    game();
    void main_update();
    void game_loop();

private:
    gamefield main_gamefield;
    graphic_enginge main_graphic_engine;
    input_handler main_input_handler;

};

#endif // GAME_H
