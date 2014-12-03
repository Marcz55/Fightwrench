#include "menu.h"

using namespace std;

menu::menu()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    Menu_width = 400;
    Menu_height = 300;

    //Skapa fönster
    Menu_window = SDL_CreateWindow("Fightwrench - The Mindless Genocide", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Menu_width, Menu_height,SDL_WINDOW_RESIZABLE);
    Menu_renderer = SDL_CreateRenderer(Menu_window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Menu_renderer, Menu_width, Menu_height);


    //Skapa bakgrunden
    Menu_surface = IMG_Load("Menybild.png");
    Background = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Button1.png");
    Button1 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Button2.png");
    Button2 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    SDL_FreeSurface(Menu_surface);

    menu_loop();
    SDL_Delay(3000);

}

menu::~menu()
{
    SDL_DestroyWindow(Menu_window);
    SDL_DestroyRenderer(Menu_renderer);
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Button1);
    SDL_DestroyTexture(Button2);
    SDL_Quit();
    IMG_Quit();
}

void menu::menu_loop()
{

}

void menu::update()
{
    //Uppdatera bakgrunden
    Background_rect.w = 400;
    Background_rect.h = 300;
    Background_rect.x = 0;
    Background_rect.y = 0;
    SDL_RenderCopy(Menu_renderer,Background,nullptr,&Background_rect);

    //Uppdatera knappar


    //Rendera
    SDL_RenderPresent(Menu_renderer);


}
