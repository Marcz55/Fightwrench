#include "graphic_engine.h"
using namespace std;
graphic_engine::graphic_engine()
{
    //Kolla så SDL fungerar
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            cerr << "Error initializing SDL" << endl;
            exit(1);
    }

    Window_width = 800;
    Window_height = 600;

    //Skapa fönster
    Window = SDL_CreateWindow("Fightwrench", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_width, Window_height);
    Renderer = SDL_CreateRenderer(Window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, Window_width, Window_height);

    //Skapa texturer
    Image_map.insert(pair<"axel",SDL_CreateTextureFromSurface(Renderer, IMG_Load("Axel.png")>);


}
