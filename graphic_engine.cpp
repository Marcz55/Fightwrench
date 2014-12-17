#include "graphic_engine.h"
#include <algorithm>    // std::max
#include <time.h>
#include <iostream>
using namespace std;

graphic_engine::graphic_engine(int win_height, int win_width, const int Window_width_scale, const int Window_height_scale)
{
    //Kolla så SDL fungerar, initiera
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    Window_height = win_height+200; // lägg till utrymme för huden
    Window_width = win_width;
    portrait_size = 0;
    srand (time(NULL));
    int backgroundrandomizer = rand() % 2 + 1;
    cout << backgroundrandomizer << endl;
    if (backgroundrandomizer == 1)
    {
        background = "desert";
    }
    if (backgroundrandomizer == 2)
    {
        background = "forest";
    }

    //Skapa fönster
    Window = SDL_CreateWindow("Fightwrench: The Mindless Genocide", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_width, Window_height,SDL_WINDOW_RESIZABLE);
    Renderer = SDL_CreateRenderer(Window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, Window_width, Window_height);

    //Skala fönstret beroende på vad som angetts i menyn
    SDL_SetWindowSize(Window,Window_width_scale,Window_height_scale);

    //Skapa ikon
    SDL_SetWindowIcon(Window,IMG_Load("Icon.png"));

    //Skapa texturer
    create_texture("Axel","head.png");
    create_texture("Marsus","Marsus.png");
    create_texture("Nassehuvud","Nassehuvud.png");
    create_texture("bullet","bullet.png");
    create_texture("grenade","grenade.png");
    create_texture("rocket","rocket2.png");
    create_texture("guided rocket","rocket2.png");
    create_texture("main_hud","wrenchhud.png");
    create_texture("char_1", "Character1.png");
    create_texture("char_2", "Character2.png");
    create_texture("Nasse", "Nasse.png");
    create_texture("health_bar", "health_bar.png");
    create_texture("ultimate_bar", "ultimate_bar.png");
    create_texture("characterbody","body.png");
    create_texture("standardcover","standardcover.png");

    create_texture("steroids","syringe.png");
    create_texture("speed_buff","speed_buff.png");
    create_texture("damage_buff","damage_buff.png");
    create_texture("firing_speed_buff","firing_speed_buff.png");
    create_texture("life","life.png");

    create_texture("explosion","explosion.png");
    create_texture("desert","desertbackground.jpg");
    create_texture("forest","forestbackground.jpg");
    create_texture("ammo_bar","ammo_bar.png");
    create_texture("body1","body1.png");
    create_texture("body2","body2.png");
    create_texture("body3","body3.png");
    create_texture("winner","skull.png");

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

void graphic_engine::draw_portrait(string name,double x_coord,double y_coord, double angle)
{
    portrait_size=std::min((int)130, (int) 130*Window_width/800);
    Current_rect.w = portrait_size;

    Current_rect.h = portrait_size;
    Current_rect.x = x_coord - Current_rect.w/2;
    Current_rect.y = y_coord - Current_rect.h/2;
    SDL_RenderCopyEx(Renderer, Image_map.at(name).Texture, nullptr, &Current_rect,angle,nullptr,SDL_FLIP_NONE);
}
void graphic_engine::display_winner(std::string port_name)
{

    draw_object("winner",Window_width/2,Window_height/2, 0);
    draw_object(port_name,Window_width/2,Window_height/2, 0);
    SDL_RenderPresent(Renderer);
    SDL_Delay(5000);


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
        draw_object(background,750,400,0);
        for(auto it = my_gamefield.character_vector.begin(); it != my_gamefield.character_vector.end(); it++)
        {
            draw_object(it->get_body_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_movement_direction());
        }
        for(auto it = my_gamefield.projectile_vector.begin(); it != my_gamefield.projectile_vector.end(); it++)
        {
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
        }
        for(auto it = my_gamefield.cover_vector.begin(); it != my_gamefield.cover_vector.end(); it++)
        {
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
        }
        for(auto it = my_gamefield.power_up_vector.begin(); it != my_gamefield.power_up_vector.end(); it++)
        {
            draw_object(it->get_name(),it->get_xpos(),it->get_ypos(),it->get_direction());
        }
        for(auto it = my_gamefield.explosion_vector.begin(); it != my_gamefield.explosion_vector.end(); it++)
        {
            draw_scaled_object("explosion",it->get_xpos()-(186*(it->get_scale())*(it->get_timer()))/10,it->get_ypos()-(186*(it->get_scale())*(it->get_timer()))/10,0,(it->get_scale()*it->get_timer())/10,(it->get_scale()*it->get_timer())/10);
        }


        draw_scaled_object("main_hud",0,Window_height - 200,0, (double) Window_width/800, 1);
        draw_portrait(my_gamefield.character_vector.at(0).get_portrait_name(), (int) 80*Window_width/800, (int) Window_height-75,0);
        draw_portrait(my_gamefield.character_vector.at(1).get_portrait_name(),(int) 720*Window_width/800, (int) Window_height-75,0);
        draw_scaled_object("health_bar",(int)180*Window_width/800, (int) Window_height - 180,0 ,(double)my_gamefield.character_vector.at(0).get_health_percent()*Window_width/800,1);
        draw_scaled_object("health_bar",(int)460*Window_width/800, (int) Window_height - 180,0 ,(double)my_gamefield.character_vector.at(1).get_health_percent()*Window_width/800,1);
        if((double)(my_gamefield.character_vector.at(0).get_ammo_percent()==0))
        {
              draw_scaled_object("ammo_bar",(int)180*Window_width/800, (int)Window_height-140,0 ,(double)(1 - my_gamefield.character_vector.at(0).get_reload_percent())*Window_width/800,1);
        }
        else
        {
              draw_scaled_object("ammo_bar",(int)180*Window_width/800, (int)Window_height-140,0 ,(double)(my_gamefield.character_vector.at(0).get_ammo_percent())*Window_width/800,1);
        }
        if((double)(my_gamefield.character_vector.at(1).get_ammo_percent()==0))
        {
            draw_scaled_object("ammo_bar",(int)460*Window_width/800, (int)Window_height-140,0 ,(double)(1 - my_gamefield.character_vector.at(1).get_reload_percent())*Window_width/800,1);
        }
        else
        {
            draw_scaled_object("ammo_bar",(int)460*Window_width/800, (int)Window_height-140,0 ,(double)(my_gamefield.character_vector.at(1).get_ammo_percent())*Window_width/800,1);
        }

        draw_scaled_object("ultimate_bar",(int)180*Window_width/800, (int)Window_height-100,0 ,(double)(1 - my_gamefield.character_vector.at(0).get_ultimate_percent())*Window_width/800,1);

        draw_scaled_object("ultimate_bar",(int)460*Window_width/800, (int)Window_height-100,0 ,(double)(1 - my_gamefield.character_vector.at(1).get_ultimate_percent())*Window_width/800,1);



        SDL_RenderPresent(Renderer);
}
