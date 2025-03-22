#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "CommonFunc.h"
class BaseObject
{
  public:

  BaseObject();
 ~BaseObject();
  void SetRect(const int &x,const int &y){rect.x=x,rect.y=y;}
  SDL_Rect GetRect() const{return rect;}
  SDL_Texture* GetObject()const {return p_object;}
  virtual bool LoadImg(std::string path,SDL_Renderer *screen);    // sử dụng hàm virtual để tái sử dụng định nghĩa hàm LoadImg của Base_Object
  void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL);
  void Free();
  protected:
    SDL_Texture* p_object;
    SDL_Rect rect;

};
#endif // BASEOBJECT_H
