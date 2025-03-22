#ifndef MAINOBJECT_H
#define MAINOBJECT_H
#include "CommonFunc.h"
#include "BaseObject.h"


class MainObject : public BaseObject
{
    public:
        MainObject();
        ~MainObject();
    enum WalkType
    {
        WALK_RIGHT=0,
        WALK_LEFT=1       //Mặc định là WALK_RIGHT
    }    ;

    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events,SDL_Renderer* screen);
    void set_clips();

    private:
        float x_val;      //độ xê dịch trái phải;
        float y_val;      //độ xê dịch trên dưới;

        float x_pos;      //vị trí nhân vật
        float y_pos;

        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[8];
        Input input_type;
        int frame;         //đang ở frame nào
        int status;        //trạng thái


};

#endif // MAINOBJECT_H
