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
    SDL_Texture* Character_select;
    SDL_Texture* Play_button;
    SDL_Texture* Character_button;
    SDL_Texture* Character1;
    SDL_Texture* Character2;
    SDL_Texture* Character3;
    SDL_Texture* Character4;
    SDL_Texture* Back;
    SDL_Surface* Menu_surface;
    SDL_Rect Menu_rect;
    SDL_Rect Play_button_rect;
    SDL_Rect Character_button_rect;
    SDL_Rect Player1_rect;
    SDL_Rect Player2_rect;
    SDL_Rect Back_rect;
    void menu_loop(soundhandler &main_soundhandler);
    void render(const int, const int, const double, const double,SDL_Texture*&, SDL_Rect &);
    void mouse_clicked(const double,const double,soundhandler&);
    void menu_music(soundhandler& main_soundhandler);
    bool checkcollision(const SDL_Rect&,const double,const double);
    std::string Player1;
    std::string Player2;
    std::map<std::string,SDL_Texture*> Characters;

};

#endif // MENU_H
