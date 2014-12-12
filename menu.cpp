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


    //Skapa bakgrunder
    Menu_surface = IMG_Load("Menybild.png");
    Background = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Character_selection2.png");
    Character_select = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);

    //Skapa knappar
    Menu_surface = IMG_Load("Knapp1.png");
    Play_button = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Knapp2.png");
    Character_button = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Character1.png");
    Character1 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Character2.png");
    Character2 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Axel.png");
    Character3 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Marsus.png");
    Character4 = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    Menu_surface = IMG_Load("Back.png");
    Back = SDL_CreateTextureFromSurface(Menu_renderer,Menu_surface);
    SDL_FreeSurface(Menu_surface);

    Player1 = "axel";
    Player2 = "marcus";

    //Skapa karaktärlista
    Characters.insert(pair<string,SDL_Texture*>("axel",Character1));
    Characters.insert(pair<string,SDL_Texture*>("marcus",Character2));
    Characters.insert(pair<string,SDL_Texture*>("jocke",Character3));
    Characters.insert(pair<string,SDL_Texture*>("markus",Character4));

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
    SDL_DestroyTexture(Character_select);
    SDL_DestroyTexture(Play_button);
    SDL_DestroyTexture(Character_button);
    SDL_DestroyTexture(Character1);
    SDL_DestroyTexture(Character2);
    SDL_DestroyTexture(Character3);
    SDL_DestroyTexture(Character4);
    SDL_DestroyTexture(Back);
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

    SDL_SetRenderDrawColor(Menu_renderer,0,0,0,255);
    SDL_RenderClear(Menu_renderer);

    //Uppdatera bakgrunden
    switch (state)
    {
    case 0: //Root
        render(Menu_width,Menu_height,0,0,Background,Menu_rect);
        if(checkcollision(Play_button_rect, mouse_x, mouse_y)){
            render(110,110,95,195,Play_button,Play_button_rect);
        } else
        {
        render(100,100,100,200,Play_button,Play_button_rect);
        }
        if(checkcollision(Character_button_rect, mouse_x, mouse_y)){
            render(110,110,195,195,Character_button,Character_button_rect);
        } else
        {
        render(100,100,200,200,Character_button,Character_button_rect);
        }
        break;
    case 1: //Character select
        render(Menu_width,Menu_height,0,0,Character_select,Menu_rect);
        if(checkcollision(Back_rect, mouse_x, mouse_y))
        {
            render(55,55,0,245,Back,Back_rect);
        } else
        {
        render(50,50,5,250,Back,Back_rect);
        }
        if(checkcollision(Player1_rect, mouse_x, mouse_y))
        {
            render(110,110,45,145,Characters.at(Player1),Player1_rect);
        } else
        {
        render(100,100,50,150,Characters.at(Player1),Player1_rect);
        }
        if(checkcollision(Player2_rect, mouse_x, mouse_y)){
            render(110,110,245,145,Characters.at(Player2),Player2_rect);
        } else
        {
        render(100,100,250,150,Characters.at(Player2),Player2_rect);
        }
        break;
    //Uppdatera knappar

}
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
        if(checkcollision(Play_button_rect,x,y))
        {
            main_soundhandler.play_sound("Axel");
            state = 1;
            break;
        }
        if(checkcollision(Character_button_rect,x,y))
        {
            SDL_DestroyWindow(Menu_window);
            SDL_DestroyRenderer(Menu_renderer);
            SDL_DestroyTexture(Background);
            SDL_DestroyTexture(Play_button);
            SDL_DestroyTexture(Character_button);
            main_soundhandler.stopbgm();
            main_soundhandler.playbgm();
            game main_game(main_soundhandler, 800, 1500, Player1, Player2); // sätt in önskad fönsterstorlek
            main_game.game_loop();
        }
        break;
    case 1:
        if(checkcollision(Back_rect,x,y))
        {
            state = 0;
            break;
        }
        if(checkcollision(Player1_rect,x,y))
        {
            auto it1 = Characters.find(Player1);
            do
            {
            if((++it1) == Characters.end())
            {
                it1 = Characters.begin();
                Player1 = it1->first;
            } else {
                Player1 = it1->first;
            }
            }while(Player1 == Player2);

            cout << Player1;
            break;
        }
        if(checkcollision(Player2_rect,x,y))
        {
            auto it2 = Characters.find(Player2);
            do
            {
            if((++it2) == Characters.end())
            {
                it2 = Characters.begin();
                Player2 = it2->first;
            } else {
                Player2 = it2->first;
            }
            }while(Player1 == Player2);

            cout << Player2;
        }
        break;

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
