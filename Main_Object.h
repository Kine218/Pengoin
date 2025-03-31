#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include "Common_Function.h"
#include "Base_Object.h"

// thông số tốc độ
#define GRAVITY 2
#define MAX_FALL_SPEED 20
#define PLAYER_SPEED  16
#define MAX_PLAYER_SPEED 16
#define PLAYER_JUMP_VAL 20
//
#include "Music.h"

class Main_Object : public Base_Object
{
    public:
        Main_Object();
        ~Main_Object();

    std::string Get_Score();

    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events,SDL_Renderer* screen);
    void set_clips();

    void Doplayer  (Map& map_data);
    void CheckToMap(Map& map_data);
    bool CheckDead (Map& map_data);

    void SetMapXY (const int map_x_,const int map_y_){map_x=map_x_;map_y=map_y_;}
    void CenterEntityOnMap(Map& map_data);

    private:
        float x_val;      //độ xê dịch trái phải;
        float y_val;      //độ xê dịch trên dưới;
        int score=0;
        float x_pos;      //vị trí nhân vật
        float y_pos;

        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[8];
        Input input_type;
        int frame;        //đang ở frame nào

        bool on_ground=false;
        bool OverJump=false;
        int map_x;
        int map_y;

};

#endif // MAIN_OBJECT_H
