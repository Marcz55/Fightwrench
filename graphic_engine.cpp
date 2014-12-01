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
    create_texture("Axel","Axel.png");
    create_texture("Marsus","Marsus.png");

}

void graphic_engine::create_texture(string texture_name, const char *texture_file)
{
    SDL_Surface* Create_surface = IMG_Load(texture_file);
    Image_map.insert(pair<string,Texture_struct>(texture_name,Texture_struct{Create_surface->w,Create_surface->h,SDL_CreateTextureFromSurface(Renderer,Create_surface)}));
}

void graphic_engine::draw_object(string name,double x_coord,double y_coord, double angle)
{
    Current_rect.w = Image_map.at(name).Texture_width;
    Current_rect.h = Image_map.at(name).Texture_height;
    Current_rect.x = x_coord;
    Current_rect.y = y_coord;
    SDL_RenderCopyEx(Renderer, Image_map.at(name).Texture, nullptr, &Current_rect,angle,nullptr,SDL_FLIP_NONE);
}

void graphic_engine::draw_all()
{
        //Måste ta in en lista med alla objekt som ska renderas och köra draw_object till alla!
        //Test för att rita ut 2 objekt
        for(int i = 0; i < 1000; i++)
        {
        SDL_SetRenderDrawColor(Renderer,0,0,0,255);
        SDL_RenderClear(Renderer);

        draw_object("Axel",i,i,i);
        draw_object("Marsus",800-i,600-i,-i);

        SDL_RenderPresent(Renderer);
        SDL_Delay(10);
        }
}
