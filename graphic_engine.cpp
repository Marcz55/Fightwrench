#include "graphic_engine.h"
using namespace std;

graphic_engine::graphic_engine()
{
    //Kolla så SDL fungerar, initiera
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    Window_width = 800;
    Window_height = 800;

    //Skapa fönster
    Window = SDL_CreateWindow("Fightwrench", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_width, Window_height,SDL_WINDOW_RESIZABLE);
    Renderer = SDL_CreateRenderer(Window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, Window_width, Window_height);

    //Skapa texturer
    create_texture("Axel","Axel.png");
    create_texture("Marsus","Marsus.png");
    create_texture("bullet","bullet.png");
    create_texture("grenade","grenade.png");
    create_texture("main_hud","wrenchhud.png");
    create_texture("char_1", "Knapp1.png");
    create_texture("char_2", "Knapp2.png");
    create_texture("health_bar", "health_bar.png");
    create_texture("ultimate_bar", "ultimate_bar.png");

}

void graphic_engine::create_texture(string texture_name, const char *texture_file)
{
    SDL_Surface* Create_surface = IMG_Load(texture_file);
    Image_map.insert(pair<string,Texture_struct>(texture_name,Texture_struct{Create_surface->w,Create_surface->h,SDL_CreateTextureFromSurface(Renderer,Create_surface)}));
    SDL_FreeSurface(Create_surface);
}
//för att smidigt kunna rita ut healthbars etc /marpe163
void graphic_engine::draw_scaled_object(string name, double x_coord, double y_coord, double angle, double x_scale, double y_scale)
{
    Current_rect.w = Image_map.at(name).Texture_width*x_scale;
    Current_rect.h = Image_map.at(name).Texture_height*y_scale;
    Current_rect.x = x_coord;
    Current_rect.y = y_coord;
    SDL_RenderCopyEx(Renderer, Image_map.at(name).Texture, nullptr, &Current_rect,angle,nullptr,SDL_FLIP_NONE);
}
void graphic_engine::draw_object(string name,double x_coord,double y_coord, double angle)
{
    Current_rect.w = Image_map.at(name).Texture_width;
    Current_rect.h = Image_map.at(name).Texture_height;
    Current_rect.x = x_coord - Current_rect.w/2;
    Current_rect.y = y_coord - Current_rect.h/2;
    SDL_RenderCopyEx(Renderer, Image_map.at(name).Texture, nullptr, &Current_rect,angle,nullptr,SDL_FLIP_NONE);
}

graphic_engine::~graphic_engine()
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Renderer = nullptr;
    Window = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void graphic_engine::draw_all(gamefield& my_gamefield)
{
    //Måste ta in en lista med alla objekt som ska renderas och köra draw_object till alla!
    //Test för att rita ut 2 objekt
        SDL_SetRenderDrawColor(Renderer,0,0,0,255);
        SDL_RenderClear(Renderer);
        for(auto it = my_gamefield.character_vector.begin(); it != my_gamefield.character_vector.end(); it++)
        {
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
        }
        for(auto it = my_gamefield.projectile_vector.begin(); it != my_gamefield.projectile_vector.end(); it++)
        {
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
        }

        draw_object("main_hud",400,700,0);
        draw_object("Axel", 65, 725,0);
        draw_object("Marsus",735, 725,0);
        draw_scaled_object("health_bar",180, 620,0 ,0.75,1);
        draw_scaled_object("health_bar",460, 620,0 ,0.4,1);
        draw_scaled_object("ultimate_bar",180, 660,0 ,0.60,1);
        draw_scaled_object("ultimate_bar",460, 660,0 ,0.35,1);



        SDL_RenderPresent(Renderer);
}
