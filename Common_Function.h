#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

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
const int FPS=30;
//tile
#define TILE_SIZE 64
#define MAX_MAP_X 4000
#define MAX_MAP_Y 20
#define MAX_TILES 30

const SDL_Color mint =  {20, 193, 225, 1};
const SDL_Color white= { 12, 60, 88, 1};
//const SDL_Color white= {255,255,255,255};
typedef struct Input
{
    int jump;
};
struct Map
{
    int    start_x;
    int    start_y;

    int    max_x;
    int    max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

void RenderText(const std::string& text, int x, int y, SDL_Color color);

#endif // COMMON_FUNCTION_H
