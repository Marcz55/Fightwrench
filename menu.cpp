#include "menu.h"

using namespace std;

menu::menu(soundhandler &main_soundhandler)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Error initializing SDL" << endl;
        exit(1);
    }

    Menu_width = 400;
    Menu_height = 300;
    state = 0;

    //Skapa fönster
    Menu_window = SDL_CreateWindow("Fightwrench - The Mindless Genocide", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Menu_width, Menu_height,SDL_WINDOW_RESIZABLE);
    Menu_renderer = SDL_CreateRenderer(Menu_window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Menu_renderer, Menu_width, Menu_height);


    //Skapa bakgrunden
    Menu_surface = IMG_Load("Menybild.png");
    Background = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);

    //Skapa knappar
    Menu_surface = IMG_Load("Knapp1.png");
    Button1 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Knapp2.png");
    Button2 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    SDL_FreeSurface(Menu_surface);

    //Sätt igång menymusik
    menu_music(main_soundhandler);

    //Starta menyloop
    menu_loop(main_soundhandler);

}

menu::~menu()
{
    SDL_DestroyWindow(Menu_window);
    SDL_DestroyRenderer(Menu_renderer);
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Button1);
    SDL_DestroyTexture(Button2);
    IMG_Quit();
    SDL_Quit();
}

void menu::menu_loop(soundhandler& main_soundhandler)
{
    double mouse_x = 0;
    double mouse_y = 0;

    for(int i = 0; i>-1; ++i)
    {
        SDL_Event listen;
        while (SDL_PollEvent(&listen))
        {
            if(listen.type == SDL_MOUSEMOTION){
                mouse_x = listen.motion.x;
                mouse_y = listen.motion.y;
            }
            else if(listen.type == SDL_MOUSEBUTTONDOWN)
            {
                mouse_clicked(mouse_x,mouse_y,main_soundhandler);
            }

        }
        update(mouse_x,mouse_y);
        SDL_Delay(10);
    }
}

void menu::render(const int w, const int h, const double x, const double y, SDL_Texture *&texture, SDL_Rect &rect)
{
    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(Menu_renderer,texture,nullptr,&rect);
}

void menu::update(const double mouse_x,const double mouse_y)
{
    //Uppdatera bakgrunden
    switch (state)
    {
    case 0:
        render(Menu_width,Menu_height,0,0,Background,Menu_rect);
        if(checkcollision(Button1_rect, mouse_x, mouse_y)){
            render(110,110,95,195,Button1,Button1_rect);
        } else
        {
        render(100,100,100,200,Button1,Button1_rect);
        }
        if(checkcollision(Button2_rect, mouse_x, mouse_y)){
            render(110,110,195,195,Button2,Button2_rect);
        } else
        {
        render(100,100,200,200,Button2,Button2_rect);
        }
        break;
    }
    //Uppdatera knappar


    //Rendera
    SDL_RenderPresent(Menu_renderer);


}

void menu::menu_music(soundhandler& main_soundhandler)
{
    main_soundhandler.playbgm("Menu_music");
}

void menu::mouse_clicked(const double x, const double y,soundhandler& main_soundhandler)
{
    switch (state)
    {
    case 0:
        cout << "x: " << x << " y: " << y << "\n";
        if(checkcollision(Button1_rect,x,y))
        {
            main_soundhandler.play_sound("Axel");
            cout << "Button 1 clicked!";
        }
        if(checkcollision(Button2_rect,x,y))
        {
            SDL_DestroyWindow(Menu_window);
            SDL_DestroyRenderer(Menu_renderer);
            SDL_DestroyTexture(Background);
            SDL_DestroyTexture(Button1);
            SDL_DestroyTexture(Button2);
            main_soundhandler.stopbgm();
            main_soundhandler.playbgm();
            game main_game(main_soundhandler);
            main_game.game_loop();
            cout << "Button 2 clicked!";
        }
        break;

        //Fler cases
    }
}

bool menu::checkcollision(const SDL_Rect& rect,const double x,const double y)
{
    if((x > rect.x && x < rect.x + rect.w) && (y > rect.y && y < rect.y + rect.h))
    {
        return true;
    } else {
        return false;
    }
}
