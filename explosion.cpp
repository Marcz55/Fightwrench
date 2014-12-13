#include "explosion.h"

explosion::explosion(double init_scale, double init_x, double init_y, class gamefield *init_gamefield)
{
    main_gamefield = init_gamefield;
    xpos = init_x;
    ypos = init_y;
    scale = init_scale;
}

void explosion::update()
{
    if (explosion_timer > 0)
    {
        explosion_timer -= 1;
    }
}
