#include "menu.h"
#include "graphic_engine.h"
#include "gamefield.h"
#include "soundhandler.h"
#include "input_handler.h"
#include "game.h"

using namespace std;


int main(int, char **)
{

    soundhandler main_soundhandler;
    menu m(main_soundhandler);

    return 0;
}
