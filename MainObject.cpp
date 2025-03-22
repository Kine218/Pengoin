#include "MainObject.h"
MainObject::MainObject()
{
    frame=0;
    x_pos=320;
    y_pos=320;
    x_val=0;
    y_val=0;
    width_frame=60;
    height_frame=64;
    status=-1;  // cố định trong game này
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImg(path, screen);
    if (ret==true)
    {
        width_frame=rect.w/8;
        height_frame=rect.h;

    }

}

void MainObject::set_clips()
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

void MainObject::Show(SDL_Renderer* des)
{
   if (status==WALK_RIGHT)
   {
       LoadImg("img//player_right.png",des);
   }
   if (status==WALK_LEFT)
   {
       LoadImg("img//player_left.png",des);
   }
   if (input_type.left==1||input_type.right==1)
       frame++;
   else
   {
       frame=0;
   }
   frame%=8;
   rect.x =x_pos;
   rect.y =y_pos;

   SDL_Rect* current_clip =&frame_clip[frame];

   SDL_Rect renderQuad= {rect.x,rect.y,width_frame,height_frame};

   SDL_RenderCopy(des,p_object,current_clip,&renderQuad);

}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            {
            status=WALK_RIGHT;
            input_type.right=1;
            }
            break;
            case SDLK_a:
            {
            status=WALK_LEFT;
            input_type.left=1;
            }
            break;
            default: break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {

    }
}
