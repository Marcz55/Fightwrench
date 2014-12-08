#ifndef GAME_H
#define GAME_H
#include "gamefield.h"
#include "graphic_engine.h"
#include "input_handler.h"
#include "axel.h"
#include "marcus.h"
#include "soundhandler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>


class game
{
public:
    game(soundhandler &main_soundhandler);
    void main_update();
    void game_loop();

private:
    gamefield main_gamefield;
    graphic_engine main_graphic_engine;
    input_handler main_input_handler;
};

#endif // GAME_H
