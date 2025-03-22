#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

class TileMat : public BaseObject
{
   public:
       TileMat(){}
       ~TileMat(){}


};
class GameMap
{
public:
    GameMap(){}
    ~GameMap(){}
    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    int map_run=0;

private:
    Map game_map;
    TileMat tile_mat[MAX_TILES];

};
#endif // GAME_MAP_H
