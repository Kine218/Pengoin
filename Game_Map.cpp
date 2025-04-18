#include "Game_Map.h"
#include "Common_Function.h"
#include <iostream>

void Game_Map::LoadMap(char* name)
{
    FILE* fp = nullptr;
    fopen_s(&fp, name ,"rb");
    if (fp==nullptr)
        return;
    game_map.max_x=0;
    game_map.max_y=0;
    for (int i=0;i<MAX_MAP_Y;i++)
    {  for (int j=0;j<MAX_MAP_X;j++)
      {
         fscanf(fp ,"%d", &game_map.tile[i][j]);
        int val = game_map.tile[i][j];
        if (val>0)
        {
            if (j>game_map.max_x)
            {
                game_map.max_x=j;
            }
            if (i>game_map.max_y)
            {
                game_map.max_y=i;
            }
        }
      }
    }
    game_map.max_x=(game_map.max_x+1)*TILE_SIZE;
    game_map.max_y=(game_map.max_y+1)*TILE_SIZE;

    game_map.start_y=0;
    game_map.file_name=name;
    fclose(fp);
}

void Game_Map::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp=nullptr;
    for (int i=0;i<MAX_TILES;i++)
    {
        sprintf_s(file_img,"map/%d.png",i);
        fopen_s(&fp,file_img,"rb");
        if (fp==nullptr)
        {
            continue;
        }
        fclose(fp);
        tile_mat[i].LoadImg(file_img,screen);
    }
}

void Game_Map::DrawMap(SDL_Renderer* screen)
{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;

    int map_x=0;
    int map_y=0;

    map_x=game_map.start_x/TILE_SIZE;
    map_y=game_map.start_y/TILE_SIZE;

    x1=(game_map.start_x%TILE_SIZE)*-1;
    x2=x1+SCREEN_WIDTH + (x1==0?0:TILE_SIZE);

    y1=(game_map.start_y%TILE_SIZE)*-1;
    y2=y1+SCREEN_HEIGHT +(y1==0?0:TILE_SIZE);

    for (int i=y1;i<y2;i+=TILE_SIZE)
    {   map_x=game_map.start_x/TILE_SIZE;
        for (int j=x1;j<x2;j+=TILE_SIZE)
        {
            int val=game_map.tile[map_y][map_x];
            if (val>0)
            {
                int tileX=j;
                int tileY=i;
                if (val==20) tileY+=3;
                tile_mat[val].SetRect(tileX,tileY);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
