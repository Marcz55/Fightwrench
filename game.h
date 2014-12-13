#ifndef GAME_H
#define GAME_H
#include "gamefield.h"
#include "graphic_engine.h"
#include "input_handler.h"
#include "axel.h"
#include "marcus.h"
#include "soundhandler.h"
#include "standardcover.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>


class game
{
public:
    game(soundhandler &main_soundhandler, int window_height = 600, int window_width = 800, const std::string Player1 = "", const std::string Player2 = "");
    void main_update();
    void game_loop();
    void firstmap();

private:
    gamefield main_gamefield;
    graphic_engine main_graphic_engine;
    input_handler main_input_handler;
    bool running;
};

#endif // GAME_H
