#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include "../game/VoxelEngine.h"

class Game
{
private:
    VoxelEngine voxelengine;
    
public:
    Game();
    ~Game();

    void onPlayerMove();

    void event();

    void draw();
    void init(const char* playerName);
};




#endif