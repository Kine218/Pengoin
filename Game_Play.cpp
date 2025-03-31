#include "Game_Play.h"

Base_Object g_background;
Base_Object g_menu;
Base_Object g_setting;

Base_Object g_slider1;
Base_Object g_slider2;

Game_Map GAME_MAP;
Music g_music;
TTF_Font *gFont = nullptr;
std::string SCORE;

int slider1X=560;
int slider1Y=225;

int slider2X=560;
int slider2Y=300;

const int slider_Min=480;
const int slider_Max=640;

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
        if (p_player.CheckJump==true)
        {g_music.JumpSound();
         p_player.CheckJump=false;
        }
        //  Spawning(p_enemy,g_screen);
        if (score.size()<4||(score.size()==4&&score<"150 "))
        RenderText("Press Space or click Left mouse button to jump",50,570,white);
        SDL_RenderPresent(g_screen);


       int real_imp_timer=fps_timer.get_ticks();
       if (real_imp_timer<FPS)
       SDL_Delay(1000/FPS-real_imp_timer);

    }
    g_music.GameOver();
    SDL_RenderPresent(g_screen);
    SDL_Delay(100);
}

void Setting()
{
    g_setting.LoadImg("img/setting.png",g_screen);
    g_slider1.LoadImg("img/scroll.png",g_screen);
    bool setting_isrunning=true;

    int mouseX,mouseY;  //lấy tọa độ chuột

    bool quit=false;
    bool slider1touch=false;
    bool slider2touch=false;
    bool reset=false;
    while(setting_isrunning)
    {     g_setting.Render(g_screen);
          SDL_GetMouseState(&mouseX,&mouseY);

    //thanh âm thanh nền
            slider1touch=false;
            slider2touch=false;

        if (mouseX>=slider1X&&mouseX<=slider1X+13&&mouseY>=slider1Y&&mouseY<=slider1Y+40)
            slider1touch=true;
        if (mouseX>=slider2X&&mouseX<=slider2X+13&&mouseY>=slider2Y&&mouseY<=slider2Y+40)
            slider2touch=true;
    //slider1
        g_slider1.SetRect(slider1X,slider1Y);
        g_slider1.Render(g_screen);
    //slider2
        g_slider1.SetRect(slider2X,slider2Y);
        g_slider1.Render(g_screen);

        if (mouseX>=700&&mouseX<=850&&mouseY>=490&&mouseY<=510)
            {quit=true;
            RenderText("Quit",745,492,mint);
            }
        else
            RenderText("Quit",745,492,white);

        if (mouseX>=445&&mouseX<=595&&mouseY>=490&&mouseY<=510)
            {reset=true;
            RenderText("Default",480,492,mint);
            }
        else
            RenderText("Default",480,492,white);

            RenderText("~Background Music : "+g_music.getBackvolumn(slider1X)+"%",450,200,mint);
            RenderText("~Sound Effects : "+g_music.getEffectvolumn(slider2X)+"%",450,275,mint);


    //
         while (SDL_PollEvent(&g_event)!=0)
        {
                 if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT)
              { g_music.ClickSound();

                if (quit)
                   {
                    setting_isrunning=false;
                   }
                if (reset)
                   {
                    slider1X=560;
                    slider2X=560;
                    g_music.backgroundmusic_change(slider1X);
                    g_music.soundeffect_change(slider2X);
                    reset=false;
                   }

              }
               if (g_event.type ==SDL_MOUSEMOTION&&g_event.button.button == SDL_BUTTON_LEFT)
               {
                   if (slider1touch)
                  {
                    slider1X=mouseX-7;
                    if (slider1X<=slider_Min) slider1X=slider_Min;
                    if (slider1X>=slider_Max) slider1X=slider_Max;
                    g_music.backgroundmusic_change(slider1X);
                  }
                    if (slider2touch)
                  {
                    slider2X=mouseX-7;
                    if (slider2X<=slider_Min) slider2X=slider_Min;
                    if (slider2X>=slider_Max) slider2X=slider_Max;
                    g_music.soundeffect_change(slider2X);
                  }
               }
        }

        SDL_RenderPresent(g_screen);
        SDL_RenderClear(g_screen);
    }

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


