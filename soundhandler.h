#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

class soundhandler
{
public:
    soundhandler();

    ~soundhandler();

    //Bakgrundsmusik
    Mix_Music* Soundtrack = nullptr;
    Mix_Chunk* Gunshot = nullptr;
    //Ljudeffekter
    std::map<std::string,Mix_Chunk*> Sound_map;

    void playbgm();
    void stopbgm();
    void pausebgm();
    void resumebgm();
    void rewindbgm();

    void create_sound(std::string const, const char*);
    void play_sound(std::string const);

};

#endif // SOUNDHANDLER_H
