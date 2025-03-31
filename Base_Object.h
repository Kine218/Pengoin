#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include "Common_Function.h"

class Base_Object
{ public:
  Base_Object();
 ~Base_Object();

  void SetRect(const int &x,const int &y)
  {rect.x=x,rect.y=y;}

  SDL_Rect GetRect()       const{return rect;}

  SDL_Texture* GetObject() const{return p_object;}

  virtual bool LoadImg(std::string path,SDL_Renderer *screen);    // sử dụng hàm virtual để tái sử dụng định nghĩa hàm LoadImg của Base_Object

  void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL);

  void Free();

  protected:
  SDL_Texture* p_object;
  SDL_Rect rect;

};

#endif // BASE_OBJECT_H
