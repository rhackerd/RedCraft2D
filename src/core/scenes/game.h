#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "../game/VoxelEngine.h"
#include "../networking/client.hpp"

class Game
{
private:
    VoxelEngine voxelengine;
    Client client;
    
public:
    Game();
    ~Game();

    void draw();
    void init(const char* playerName);
};




#endif