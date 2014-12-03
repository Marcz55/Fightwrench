#include "graphic_engine.h"
#include "gamefield.h"
#include "soundhandler.h"



#include "input_handler.h"
//Screen dimension constants

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int, char **)
{

    graphic_engine Test;
    gamefield g1;
    input_handler inputhandler;
    soundhandler sound;
    sound.playbgm();
    g1.add_object();
    for(int i = 0; i < 1000; i++)
    {sound.play_sound("Gunshot");
    Test.draw_all(g1);
    }

    return 0;
}
