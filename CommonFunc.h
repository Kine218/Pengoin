#ifndef COMMONFUNC_H
#define COMMONFUNC_H
#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "BaseObject.h"
//#include "random_map.h"
static SDL_Window* g_window =nullptr;
static SDL_Renderer* g_screen =nullptr;
static SDL_Event g_event;

// thông số màn hình
const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;

//tile
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define MAX_TILES 20

typedef struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;

};
struct Map
{
    int     start_x;
    int     start_y;

    int    max_x;
    int    max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};
#endif // COMMONFUNC_H
