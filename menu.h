#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

class menu
{
public:
    menu();
    ~menu();
    void update();

private:
    int Menu_width;
    int Menu_height;
    SDL_Window* Menu_window ;
    SDL_Renderer* Menu_renderer;
    SDL_Texture* Background;
    SDL_Texture* Button1;
    SDL_Texture* Button2;
    SDL_Surface* Menu_surface;
    SDL_Rect Background_rect;
    void menu_loop();

};

#endif // MENU_H
