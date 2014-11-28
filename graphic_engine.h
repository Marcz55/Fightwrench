#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

class graphic_engine
{
friend class gamefield;
private:

    int Window_width;
    int Window_height;
    SDL_Window* Window ;
    SDL_Renderer* Renderer;
    std::map<std::string,SDL_Texture*> Image_map;

public:
    ~graphic_engine() = default;
    graphic_engine();




};

#endif
