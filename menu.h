#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "game.h"

class menu
{
public:
    menu(soundhandler& main_soundhandler);
    ~menu();
    void update(const double, const double);

private:
    int Menu_width;
    int Menu_height;
    int state;
    SDL_Window* Menu_window ;
    SDL_Renderer* Menu_renderer;
    SDL_Texture* Background;
    SDL_Texture* Button1;
    SDL_Texture* Button2;
    SDL_Surface* Menu_surface;
    SDL_Rect Menu_rect;
    SDL_Rect Button1_rect;
    SDL_Rect Button2_rect;
    void menu_loop(soundhandler &main_soundhandler);
    void render(const int, const int, const double, const double,SDL_Texture*&, SDL_Rect &);
    void mouse_clicked(const double,const double,soundhandler&);
    void menu_music(soundhandler& main_soundhandler);
    bool checkcollision(const SDL_Rect&,const double,const double);

};

#endif // MENU_H
