#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Common_Function.h"
#include "Base_Object.h"

class TileMat : public Base_Object
{
   public:
       TileMat(){}
       ~TileMat(){}

};

class Game_Map
{
public:
    Game_Map(){}
    ~Game_Map(){}
    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;};
    void SetMap(Map& map_data) {game_map=map_data;};

private:
    Map game_map;
    TileMat tile_mat[MAX_TILES];

};

#endif // GAME_MAP_H
