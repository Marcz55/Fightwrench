#include "graphic_engine.h"
#include "gamefield.h"
#include "soundhandler.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int, char **)
{

    graphic_engine Test;
    gamefield g1;
    g1.add_object();
    for(int i = 0; i < 1000; i++)
    {
    Test.draw_all(g1);
    }

    return 0;
}
