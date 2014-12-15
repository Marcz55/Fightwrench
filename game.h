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
#include "power_up.h"
#include "temporary_power_up.h"
#include "permanent_power_up.h"
#include "nasse.h"


class game
{
public:
    game(soundhandler &main_soundhandler, int window_height = 600, int window_width = 800, const std::string Player1 = "", const std::string Player2 = "",const int window_height_scale = 600, const int window_width_scale = 800);
    game(const game&) = delete;
    game& operator=(const game&) = delete;
    ~game() = default;
    void main_update();
    void game_loop();
    void firstmap();
    void spawn_powerup();

private:
    gamefield main_gamefield;
    graphic_engine main_graphic_engine;
    input_handler main_input_handler;
    bool running;
    int power_up_spawn_timer = 1000;
    int window_height_scale;
    int window_width_scale;
};

#endif // GAME_H
