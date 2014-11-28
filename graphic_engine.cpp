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
    Window = SDL_CreateWindow("Fightwrench", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_width, Window_height,SDL_WINDOW_RESIZABLE);
    Renderer = SDL_CreateRenderer(Window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, Window_width, Window_height);

    //Skapa texturer
    Image_map.insert(pair<string,SDL_Texture*>("Axel",SDL_CreateTextureFromSurface(Renderer, IMG_Load("Axel.png"))));
}

void graphic_engine::draw_object(string name,double x_coord,double y_coord)
{
    Current_rect.w = 617;
    Current_rect.h = 448;
    Current_rect.x = x_coord;
    Current_rect.y = y_coord;
    SDL_RenderCopy(Renderer, Image_map.at(name), nullptr, &Current_rect);
}

void graphic_engine::draw_all()
{
    //Måste ta in en lista med alla objekt som ska renderas och köra draw_object till alla!

    SDL_SetRenderDrawColor(Renderer,0,0,0,255);
    SDL_RenderClear(Renderer);

    draw_object("Axel",0,0);

    SDL_RenderPresent(Renderer);
}
