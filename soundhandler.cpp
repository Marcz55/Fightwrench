#include "soundhandler.h"
using namespace std;
soundhandler::soundhandler()
{
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cerr << "Cannot initialize Mix" << endl;
        exit(1);
    }

    Soundtrack = Mix_LoadMUS("Testmusik.mp3");

    create_sound("Gunshot","Sound1.wav");

}

soundhandler::~soundhandler()
{
    Mix_FreeMusic(Soundtrack);
    Mix_FreeChunk(Gunshot);
    for(auto it = Sound_map.begin(); it != Sound_map.end(); ++it)
    {
        Mix_FreeChunk(it->second);
    }
    Mix_Quit();
    SDL_Quit();
}

void soundhandler::create_sound(string name, const char* filename)
{
    Mix_Chunk* Current_sound = Mix_LoadWAV(filename);
    Sound_map.insert(pair<string,Mix_Chunk*>(name, Current_sound));
    Mix_FreeChunk(Current_sound);
}

void soundhandler::play_sound(string name)
{
    Mix_PlayChannel(-1, Sound_map.at(name), 0);
}

void soundhandler::playbgm()
{
    if (Soundtrack != nullptr)
    {
        Mix_PlayMusic(Soundtrack,-1);
    } else {
        printf("Mix_LoadMUS(\"Testmusik.mp3\"): %s\n", Mix_GetError());
    }
}

void soundhandler::stopbgm()
{
    Mix_HaltMusic();
}

void soundhandler::pausebgm()
{
    if(Mix_PausedMusic() == 0)
    {
         Mix_PauseMusic();
    }

}

void soundhandler::resumebgm()
{
    Mix_ResumeMusic();
}

void soundhandler::rewindbgm()
{
    Mix_RewindMusic();
}
