#include "Main_Object.h"

Main_Object::Main_Object()
{
    frame=0;
    x_pos=0;
    y_pos=200;
    x_val=0;
    y_val=0;
    width_frame=64;
    height_frame=64;
    input_type.jump=0;
    map_x=0;
    map_y=0;
}

Main_Object::~Main_Object()
{
    //dtor
}

std::string Main_Object::Get_Score()
{
    std::string x=" ";
    int alter=score;
    while (alter>0)
    {
        x=char(alter%10+'0')+x;
        alter/=10;
    }
    return x;
}

bool Main_Object::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret=Base_Object::LoadImg(path, screen);
    return ret;
}

void Main_Object::Show(SDL_Renderer* des)
{
   if (on_ground==true)
   {
       LoadImg("img/player_right.png",des);
   }
   else
   {
       LoadImg("img/jum_right.png",des);
   }
   frame++;
   frame%=8;

   score++;

   rect.x =x_pos-map_x;
   rect.y =y_pos-map_y;

   if (on_ground) rect.y+=2;

   SDL_Rect* current_clip =&frame_clip[frame];

   SDL_Rect renderQuad= {rect.x,rect.y,width_frame,height_frame};

   SDL_RenderCopy(des,p_object,current_clip,&renderQuad);
}

void Main_Object::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_SPACE:
            {
                    if (OverJump==false)
                    {
                    input_type.jump=1;

                    }
                    OverJump=true;
                  //  status=JUMP;
            }
            default: break;
        }

    }
    else if (events.type == SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT)
    {
                if (OverJump==false)
                input_type.jump=1;
                OverJump=true;
    }
    else if (events.type == SDL_MOUSEBUTTONUP && events.button.button == SDL_BUTTON_LEFT)
    {
         OverJump=false;
    }
    else if (events.type == SDL_KEYUP)
    {     switch (events.key.keysym.sym)
        {
            case SDLK_SPACE:
            {
               OverJump=false;
            }

            default: break;
        }
    }
}

void Main_Object::set_clips()
{
       if (width_frame>0&&height_frame>0)
    {
        for(int i=0;i<8;i++)
        {
        frame_clip[i].x=i*width_frame;
        frame_clip[i].y=0;
        frame_clip[i].w=width_frame;
        frame_clip[i].h=height_frame;
        }
    }
}

void Main_Object::Doplayer(Map& map_data)
{   Music music;
    x_val+=PLAYER_SPEED;
    if (x_val>MAX_PLAYER_SPEED) x_val=MAX_PLAYER_SPEED;

    y_val+=GRAVITY;
    if(y_val>=MAX_FALL_SPEED) y_val=MAX_FALL_SPEED;

    CheckToMap(map_data);
    CenterEntityOnMap(map_data);        //căn chỉnh nhân vật

    if (input_type.jump==1)
    {   if (on_ground==true)
        {y_val= -PLAYER_JUMP_VAL;
        input_type.jump=0;
        music.JumpSound();
        }
    }
}

void Main_Object::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    //check horizontal
    int height_min=height_frame<TILE_SIZE ? height_frame:TILE_SIZE;

    x1=(x_pos+x_val)/TILE_SIZE;
    x2=(x_pos+x_val+width_frame-1)/TILE_SIZE;

    y1=(y_pos)/TILE_SIZE;
    y2=(y_pos+height_min-1)/TILE_SIZE;

    if (x1>=0 && x2< MAX_MAP_X && y1>=0 &&y2< MAX_MAP_Y)
     {

     if (x_val>0)
        if (map_data.tile[y1][x2]%10!=0||map_data.tile[y2][x2]%10!=0)
        {
            x_pos=x2*TILE_SIZE;
            x_pos-=width_frame+1;
            x_val=0;
        }
        //else x_val=0;

    if (x_val<0)
        if(map_data.tile[y1][x1]%10!=0||map_data.tile[y2][x1]%10!=0)
        {
            x_pos=(x1+1)*TILE_SIZE;
            x_val=0;
        }
     }

    //check vertical
    int width_min=width_frame<TILE_SIZE ? width_frame:TILE_SIZE;
    x1=(x_pos)/TILE_SIZE;
    x2=(x_pos+width_min)/TILE_SIZE;

    y1=(y_pos+y_val)/TILE_SIZE;
    y2=(y_pos+y_val+height_frame-1)/TILE_SIZE;

    //check chạm đất
    if (map_data.tile[y2][x1]%10!=0||map_data.tile[y2][x2]%10!=0) on_ground=true;
    else on_ground=false;

    if (x1>=0 && x2< MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
       if (y_val>0)
       {
           if (map_data.tile[y2][x1]%10!=0||map_data.tile[y2][x2]%10!=0)
           {
               y_pos=y2*TILE_SIZE;
               y_pos-=(height_frame+1);
               y_val=0;

               on_ground=true;
           }
           else on_ground=false;
       }
       if (y_val<0)
       {
           if (map_data.tile[y1][x1]%10!=0|| map_data.tile[y1][x2]%10!=0)
           {
               y_pos=(y1+1)*TILE_SIZE;
               y_val=0;
           }
       }
    }

    x_pos+=x_val;
    y_pos+=y_val;
    if (x_pos<0) x_pos=0;
}

bool Main_Object::CheckDead(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    int height_min=height_frame<TILE_SIZE ? height_frame:TILE_SIZE;

    x1=(x_pos+x_val)/TILE_SIZE;
    x2=(x_pos+x_val+width_frame-1)/TILE_SIZE;

    y1=(y_pos)/TILE_SIZE;
    y2=(y_pos+height_min-1)/TILE_SIZE;

    if (map_data.tile[y1][x2]==10||map_data.tile[y2][x2]==10||map_data.tile[y1][x2]==20||map_data.tile[y2][x2]==20)
        {
          return true;
        }
    return false;
}

void Main_Object::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x=x_pos-(SCREEN_WIDTH/4);
    if (map_data.start_x<0)
        map_data.start_x=0;
    //map_data.start_y=y_pos-(SCREEN_HEIGHT)/2;
    if (map_data.start_y<0)
        map_data.start_y=0;
}
