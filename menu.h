/*
 * menu.h och menu.cpp är, sånär som på små detaljer, skriven av Marcus Wälivaara.
 *
 * Menyn är till för att skapas i början av spelet, och skapa detta med vissa parametrar.
 * Det är i menu som spelfönstrets storlek anges, vilka karaktärer som spelare 1 respektive
 * spelare 2 ska spela som, samt vilken musik som ska spelas.
 *
 */

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
    menu(const soundhandler&) = delete;
    soundhandler& operator=(const soundhandler&) = delete;


    void update(const double, const double);

private:
    int Menu_width;
    int Menu_height;
    int state;
    int Resolution_height;
    int Resolution_width;
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
    SDL_Texture* Res800x600;
    SDL_Texture* Res1280x720;
    SDL_Texture* Res1366x768;
    SDL_Texture* Res1680x1050;
    SDL_Texture* Res1920x1080;
    SDL_Rect Menu_rect;
    SDL_Rect Play_button_rect;
    SDL_Rect Character_button_rect;
    SDL_Rect Player1_rect;
    SDL_Rect Player2_rect;
    SDL_Rect Back_rect;
    SDL_Rect Res_rect;
    void menu_loop(soundhandler &main_soundhandler);
    void render(const int, const int, const double, const double,SDL_Texture*&, SDL_Rect &);
    void mouse_clicked(const double,const double,soundhandler&);
    void menu_music(soundhandler& main_soundhandler);
    bool checkcollision(const SDL_Rect&,const double,const double);
    std::string Player1;
    std::string Player2;
    std::map<std::string,SDL_Texture*> Characters;
    std::map<int,SDL_Texture*> Resolutions;
    std::map<int,int> Heights;

};

#endif // MENU_H
