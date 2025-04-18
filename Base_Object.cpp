#include "Base_Object.h"

Base_Object::Base_Object()
{
    p_object =nullptr;
    rect.x=0;
    rect.y=0;
    rect.w=0;
    rect.h=0;
}

Base_Object::~Base_Object()
{
      Free();
}
bool Base_Object::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture  = nullptr;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface==nullptr)
        std::cout<<"unable to load image "<<path<<" SDL_image Error:"<< IMG_GetError()<<std::endl;
    else
    {
        new_texture=SDL_CreateTextureFromSurface(screen,load_surface);
        if (new_texture!=nullptr)
        {
            rect.w=load_surface->w;
            rect.h=load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object=new_texture;
    return true;
}

void Base_Object::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
   SDL_Rect renderquad ={rect.x,rect.y,rect.w,rect.h};
   SDL_RenderCopy(des,p_object,clip,&renderquad);
}

void Base_Object::Free()
{
      if (p_object!=nullptr)
   {
       SDL_DestroyTexture(p_object);
       p_object=nullptr;
       rect.w=0;
       rect.h=0;
   }
}
