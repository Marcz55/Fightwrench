#include "soundhandler.h"
using namespace std;
soundhandler::soundhandler()
{

    //Initiera SDL och SDL_Mixer

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cerr << "Cannot initialize Mix" << endl;
        exit(1);
    }

    //Lägg in musik och ljudeffekter i två maps

    create_music("Music1","Testmusik.mp3");
    create_music("Music2","8-Bit-Rebirth.mp3");
    create_music("Music3","Chase-101.mp3");
    create_music("Music4","Hellbreaker.ogg");
    create_music("Menu_music","Royal-Flush-Party.mp3");

    create_sound("Gunshot","Sound1.wav");
    create_sound("Axel","Axel_laugh.wav");
    create_sound("Explosion","explosion.wav");
    create_sound("Reload","reload.wav");
    create_sound("Rocket","Rocket.wav");


}

soundhandler::~soundhandler()
{
    for(auto it = Music_map.begin(); it != Music_map.end(); ++it)
    {
        Mix_FreeMusic(it->second);
    }
    for(auto it = Sound_map.begin(); it != Sound_map.end(); ++it)
    {
        Mix_FreeChunk(it->second);
    }
    Mix_Quit();
    SDL_Quit();
}

/* void soundhandler::create_*****(const string name, const char* filename)
 *
 * Dessa två funktioner sätter in ljud i rätt map.
 */

void soundhandler::create_music(const string name, const char* filename)
{
    Music_map.insert(pair<string,Mix_Music*>(name, Mix_LoadMUS(filename)));
}

void soundhandler::create_sound(const string name, const char* filename)
{
    Sound_map.insert(pair<string,Mix_Chunk*>(name, Mix_LoadWAV(filename)));
}

/* void soundhandler::play_sound(const string name) och void soundhandler::playbgm(const string Soundtrack)
 *
 * Spela upp ett ljud eller en bakgrundsmusik som finns lagrad i en map.
 */

void soundhandler::play_sound(const string name)
{
    if(Sound_map.at(name) != nullptr)
        Mix_PlayChannel(-1, Sound_map.at(name), 0);
}

void soundhandler::playbgm(const string Soundtrack)
{
    if (Music_map.at(Soundtrack) != nullptr)
    {
        Mix_PlayMusic(Music_map.at(Soundtrack),-1);
    } else {
        printf(Mix_GetError());
    }
}

/* void soundhandler::playbgm
 *
 * Spelar upp en slumpmässigt utvald bakgrundsmusik, som inte är Menu_music.
 */

void soundhandler::playbgm()
{
    auto it = Music_map.begin();
    srand(time(NULL));
    advance(it,rand()%(Music_map.size() - 1) + 1);
    playbgm(it->first);
}

/*
 * Följande funktioner är mycket enkla och använder SDL_Mixers inbyggda funktioner.
 */

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

/*
 * void soundhandler::setbgmvolume(int level)
 *
 * Funktion som sätter volymen på bakgrundsmusiken.
 * Kan bara ta värden mellan 0 och 128.
 */

void soundhandler::setbgmvolume(int level)
{
    if(level < 0)
        level = 0;
    if(level > 128)
        level = 128;
    Mix_VolumeMusic(level);
}
