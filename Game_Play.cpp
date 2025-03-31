#include "Game_Play.h"

Base_Object g_background;
Game_Map GAME_MAP;
Base_Object g_menu;
Music g_music;
TTF_Font *gFont = nullptr;
std::string SCORE;
bool Restart=false;

bool InitData()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer không thể khởi tạo! Lỗi: " << Mix_GetError() <<std::endl;
        return false;
    }

    bool success=true;
    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf không thể khởi tạo! Lỗi: " << TTF_GetError() <<std::endl;
        return false;
    }


    gFont = TTF_OpenFont("font/XR.ttf", 16);
    int ret=SDL_Init(SDL_INIT_VIDEO);
    if (ret<0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow("Pengoin",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (g_window==nullptr){success=false;}
    else
    {
        g_screen=SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen==nullptr)
            success=false;
        else
        {
            SDL_SetRenderDrawColor(g_screen,255,255,255,255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }

    Music::MusicInit();

    return success;

}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=nullptr;
    SDL_DestroyWindow(g_window);
    g_window=nullptr;
    TTF_CloseFont(gFont);
    gFont = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    Mix_CloseAudio();
    Music::FreeMusic();
}
bool LoadBack()
{
    bool ret=g_background.LoadImg("img/background5.png",g_screen);
    if (ret==false)
    return false;
    return true;
}
void RenderText(const std::string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_screen, textSurface);
    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(g_screen, textTexture, nullptr, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Game_Run()
{   g_music.ClickSound();
    srand(time(nullptr)+clock());
    if (LoadBack()==false) return ;
    Random_Map R;
    R.build();
    Imp_Timer fps_timer;
    Main_Object p_player;
//map
    GAME_MAP.LoadMap("map01.dat");
    GAME_MAP.LoadTiles(g_screen);

//player
    p_player.LoadImg("jum_right.png",g_screen);
    p_player.set_clips();

    bool is_quit=false;
    bool game_start=false;

    while (!is_quit)
    {
        fps_timer.start();
        game_start=false;

        std::string score=p_player.Get_Score();
        SCORE=score;

        while (SDL_PollEvent(&g_event)!=0)
        {      if (g_event.type ==SDL_KEYDOWN)
                switch (g_event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    game_start=true;
                    break;
                default: break;
                }
             if (g_event.type==SDL_QUIT)
                is_quit=true;

             p_player.HandelInputAction(g_event,g_screen);

        }
//background
        SDL_SetRenderDrawColor(g_screen,255,255,255,255);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,nullptr);
//map
        Map map_data=GAME_MAP.getMap();
//player
        p_player.SetMapXY(map_data.start_x,map_data.start_y);
        p_player.Doplayer(map_data);
        p_player.Show(g_screen);
//render
        GAME_MAP.SetMap(map_data);
        GAME_MAP.DrawMap(g_screen);
//text
        RenderText("score:", 10, 10,white);
        RenderText(score, 100, 10,mint);
//checkDead
        if (p_player.CheckDead(map_data)) is_quit=true;
//enemy
        //  Spawning(p_enemy,g_screen);

        SDL_RenderPresent(g_screen);


       int real_imp_timer=fps_timer.get_ticks();
       if (real_imp_timer<FPS)
       SDL_Delay(1000/FPS-real_imp_timer);

    }
    SDL_RenderPresent(g_screen);
}

void Setting()
{


}
void menu()
{
   g_menu.LoadImg("img/start_background.png",g_screen);
   bool menu_isrunning=true;
   while (menu_isrunning)
   {   SDL_RenderClear(g_screen);
       g_menu.Render(g_screen);
       bool playgame=false;
       bool exit=false;
       bool setting=false;
      // bool restart=false;
       int mouseX,mouseY;
       SDL_GetMouseState(&mouseX,&mouseY);
     //  if (score!=" ") restart=true;
       if (!Restart)
    {  if (mouseX>=200&&mouseX<=500&&mouseY>=200&&mouseY<250)
       {playgame=true;
       RenderText("PLAY GAME", 200, 200, mint);
       }
       else RenderText("Play Game", 200, 200, white);


       if (mouseX>=200&&mouseX<=500&&mouseY>=250&&mouseY<300)
       { setting=true;
       RenderText("Settings", 200, 250, mint);
       }
       else RenderText("Settings", 200, 250, white);


       if (mouseX>=200&&mouseX<=500&&mouseY>=300&&mouseY<=350)
       { exit=true;
        RenderText("Exit:(", 200, 300, mint);
       }
       else RenderText("Exit:(", 200, 300,white);

    }
       else
    {   RenderText("Score:", 200, 200, mint);
        RenderText(SCORE, 290, 200, mint);

        if (mouseX>=200&&mouseX<=500&&mouseY>=250&&mouseY<300)
       {playgame=true;
       RenderText("Restart", 200, 250, mint);
       }
       else RenderText("Restart", 200, 250, white);


       if (mouseX>=200&&mouseX<=500&&mouseY>=300&&mouseY<350)
       { setting=true;
       RenderText("Settings", 200, 300, mint);
       }
       else RenderText("Settings", 200, 300, white);


       if (mouseX>=200&&mouseX<=500&&mouseY>=350&&mouseY<=400)
       { exit=true;
        RenderText("Exit:(", 200, 350, mint);
       }
       else RenderText("Exit:(", 200, 350,white);

        g_menu.LoadImg("img/restart.png",g_screen);
    }

        while (SDL_PollEvent(&g_event)!=0)
        {
                 if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT)
              { g_music.ClickSound();

                if (playgame)
                   { Game_Run();
                    menu_isrunning=false;
                   }
                else if (exit)
                   {
                    SDL_Delay(250);
                    close();
                    menu_isrunning=false;
                   }
                else if (setting)
                   {
                     Setting();
                   }
              }
        }
       SDL_RenderPresent(g_screen);
   }
   Restart=true;
}


void Game_Play::Game_play()
{
    if (InitData()==false) return ;

    g_music.PlayBackgroundMusic();
     menu();
     while (Restart)
        menu();
        close();
}


