#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "gamefield.h"

struct Texture_struct{
    int Texture_width;
    int Texture_height;
    SDL_Texture* Texture;
};

class graphic_engine
{
private:

    int Window_width;
    int Window_height;
    int Window_height_scale;
    int Window_width_scale;
    SDL_Window* Window ;
    SDL_Renderer* Renderer;
    std::map<std::string,Texture_struct> Image_map;
    SDL_Rect Current_rect;
    int portrait_size;
    std::string background;

public:
    ~graphic_engine();
    graphic_engine(int win_height = 600, int win_width = 800, const int Window_width_scale = 600, const int Window_height_scale = 800);
    graphic_engine(const graphic_engine&) = delete;
    soundhandler& operator=(const soundhandler&) = delete;
    void draw_all(gamefield &my_gamefield);
    void draw_scaled_object(std::string name, double x_coord, double y_coord, double angle, double x_scale, double y_scale);
    void draw_portrait(string name,double x_coord,double y_coord, double angle);
    void draw_object(string name,double x_coord,double y_coord, double angle);
    void create_texture(std::string texture_name, const char *texture_file);
    void display_winner(std::string port_name);






};

#endif
