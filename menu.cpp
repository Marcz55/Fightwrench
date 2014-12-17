/*
 * menu.h och menu.cpp är, sånär som på små detaljer, skriven av Marcus Wälivaara.
 *
 * Menyn är till för att skapas i början av spelet, och skapa detta med vissa parametrar.
 * Det är i menu som spelfönstrets storlek anges, vilka karaktärer som spelare 1 respektive
 * spelare 2 ska spela som, samt vilken musik som ska spelas.
 *
 */

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
    Resolution_height = 600;
    Resolution_width = 800;
    Running = true;

    //Skapa fönster
    Menu_window = SDL_CreateWindow("Fightwrench - The Mindless Genocide", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Menu_width, Menu_height,SDL_WINDOW_RESIZABLE);
    Menu_renderer = SDL_CreateRenderer(Menu_window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Menu_renderer, Menu_width, Menu_height);

    //Skapa ikon
    SDL_SetWindowIcon(Menu_window,IMG_Load("Icon.png"));

    //Skapa bakgrunder
    Background = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Menybild.png"));
    Character_select = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("VS.png"));

    //Skapa knappar

    Character_button = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Knapp1.png"));
    Play_button = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Knapp2.png"));
    Character1 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Character1.png"));
    Character2 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Character2.png"));
    Character3 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Nasse.png"));
    Back = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("Back.png"));
    Res800x600 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("800x600.png"));
    Res1280x720 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("1280x720.png"));
    Res1366x768 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("1366x768.png"));
    Res1680x1050 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("1680x1050.png"));
    Res1920x1080 = SDL_CreateTextureFromSurface(Menu_renderer,IMG_Load("1920x1080.png"));

    Player1 = "axel";
    Player2 = "marcus";

    //Skapa karaktärlista
    Characters.insert(pair<string,SDL_Texture*>("axel",Character1));
    Characters.insert(pair<string,SDL_Texture*>("marcus",Character2));
    Characters.insert(pair<string,SDL_Texture*>("nasse",Character3));

    //Skapa lista med olika skärmupplösningar, bredden är unik för varje upplösning, varför den används för att ta reda på vilken bild som ska visas.
    Resolutions.insert(pair<int,SDL_Texture*>(800,Res800x600));
    Resolutions.insert(pair<int,SDL_Texture*>(1280,Res1280x720));
    Resolutions.insert(pair<int,SDL_Texture*>(1366,Res1366x768));
    Resolutions.insert(pair<int,SDL_Texture*>(1680,Res1680x1050));
    Resolutions.insert(pair<int,SDL_Texture*>(1920,Res1920x1080));

    //Skapa en lista med motsvarande höjd vör varje bredd
    Heights.insert(pair<int,int>(800,600));
    Heights.insert(pair<int,int>(1280,720));
    Heights.insert(pair<int,int>(1366,768));
    Heights.insert(pair<int,int>(1680,1050));
    Heights.insert(pair<int,int>(1920,1080));

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
    SDL_DestroyTexture(Back);
    for(auto it = Characters.begin(); it != Characters.end(); ++it)
    {
        SDL_DestroyTexture(it->second);
    }
    for(auto it = Resolutions.begin(); it != Resolutions.end(); ++it)
    {
        SDL_DestroyTexture(it->second);
    }
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
            if(listen.type == SDL_QUIT)
            {
                if(state == 1)
                {
                    state = 0;
                }
                else
                {
                    return;
                }
            }

            if(listen.type == SDL_MOUSEMOTION){
                mouse_x = listen.motion.x;
                mouse_y = listen.motion.y;
            }
            else if(listen.type == SDL_MOUSEBUTTONDOWN)
            {
                mouse_clicked(mouse_x,mouse_y,main_soundhandler);
            }

        }
        if(!Running)
            return;
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

    /*
     * Denna del av koden är till för att uppdatera menyfönstret. Menyn har flera states, ett för varje
     * fönster i menyn. När musen är över en knapp skall den renderas i en större storlek.
     */
    switch (state)
    {
    case 0: //Root
        render(Menu_width,Menu_height,0,0,Background,Menu_rect);
        if(checkcollision(Play_button_rect, mouse_x, mouse_y)){
            render(110,110,225,145,Play_button,Play_button_rect);
        } else
        {
        render(100,100,230,150,Play_button,Play_button_rect);
        }
        if(checkcollision(Character_button_rect, mouse_x, mouse_y)){
            render(110,110,65,145,Character_button,Character_button_rect);
        } else
        {
        render(100,100,70,150,Character_button,Character_button_rect);
        }
        if(checkcollision(Res_rect, mouse_x, mouse_y)){
            render(60,30,330,270,Resolutions.at(Resolution_width),Res_rect);
        } else
        {
        render(50,20,335,275,Resolutions.at(Resolution_width),Res_rect);
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

}
    //Rendera
    SDL_RenderPresent(Menu_renderer);

}

void menu::menu_music(soundhandler& main_soundhandler)
{
    main_soundhandler.playbgm("Menu_music");
}

/*
 * Följande del i koden kollar var någonstans man klickar. Beroende på vilket
 * menyfönster vi är i kommer kollision mot olika knappar att kollas. I character
 * select är tanken att man ska kunna klicka på ett av porträtten för att byta till
 * en ledig karaktär. Denna kod finns här.
 */

void menu::mouse_clicked(const double x, const double y,soundhandler& main_soundhandler)
{
    switch (state)
    {
    case 0:
        if(checkcollision(Character_button_rect,x,y))
        {
            main_soundhandler.play_sound("Axel");
            state = 1;
            break;
        }
        if(checkcollision(Play_button_rect,x,y))
        {
            SDL_DestroyWindow(Menu_window);
            SDL_DestroyRenderer(Menu_renderer);
            SDL_DestroyTexture(Background);
            SDL_DestroyTexture(Play_button);
            SDL_DestroyTexture(Character_button);
            main_soundhandler.stopbgm();
            main_soundhandler.playbgm();
            game main_game(main_soundhandler, 800, 1500, Player1, Player2,Resolution_width,Resolution_height); // sätt in önskad fönsterstorlek, vilka karaktärer som ska vara med och vilken storlek fönstret ska ha!
            main_game.game_loop();
            Running = false;
            return;
        }
        if(checkcollision(Res_rect,x,y))
        {
            auto it = Resolutions.find(Resolution_width);
            if((++it) == Resolutions.end())
            {
                it = Resolutions.begin();
                Resolution_width = it->first;
                Resolution_height = Heights.at(Resolution_width);
            } else {
                Resolution_width = it->first;
                Resolution_height = Heights.at(Resolution_width);
            }
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
