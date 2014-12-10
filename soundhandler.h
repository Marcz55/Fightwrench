#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <time.h>

class soundhandler
{
public:
    soundhandler();
    soundhandler(const soundhandler&) = default;
    soundhandler& operator=(const soundhandler&) = default;
    ~soundhandler();

    //Bakgrundsmusik
    std::map<std::string,Mix_Music*> Music_map;

    //Ljudeffekter
    std::map<std::string,Mix_Chunk*> Sound_map;

    void playbgm(const std::string);
    void playbgm();
    void stopbgm();
    void pausebgm();
    void resumebgm();
    void rewindbgm();

    void create_sound(std::string const, const char*);
    void create_music(std::string const, const char*);
    void play_sound(std::string const);

};

#endif // SOUNDHANDLER_H
