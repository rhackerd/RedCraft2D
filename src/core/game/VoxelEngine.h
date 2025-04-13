#ifndef VOXELENGINE_H
#define VOXELENGINE_H
#include "../blocks/blocks.h"
#include "../definitions.h"
#include "terrain/terrain.h"
#include "normal/normal.h"

#include <vector>
#include <memory>
#include <string>

//TODO : Rewrite

class VoxelEngine
{
private:
    // objects
    Terrain o_terrain;
    Normal o_normal;

    std::pair<float, float> offset;
    std::pair<float, float> playerPosition;
    std::pair<float, float> windowSizeBeforeResize;

    Vector2 speed;

    Camera2D camera;

    float maxSpeed;
    float acceleration;
    float decelerationFactor;

    // networking variables
    bool playerMoved = false;

    std::string playerName;
public:
    VoxelEngine();
    ~VoxelEngine();

    void updateOffset();
    void onPlayerMove();

    void setPlayerPosition(std::pair<float, float> position) { playerPosition = position; }
    void setPlayerMoved(bool moved) { playerMoved = moved; }
    void setPlayerName(const char* name) { playerName = name; }
    void setAcceleration(float acceleration) { this->acceleration = acceleration; }
    void setDecelerationFactor(float decelerationFactor) { this->decelerationFactor = decelerationFactor; }
    void setMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }



    std::pair<float, float> getPlayerPosition() { return playerPosition; }
    bool getPlayerMoved() { return playerMoved; }
    std::string getPlayerName() { return playerName; }
    float getAcceleration() { return acceleration; }
    float getDecelerationFactor() { return decelerationFactor; }
    float getMaxSpeed() { return maxSpeed; }


    void drawOtherPlayer(std::pair<float, float> position, const char* name);
    void draw();
    void event();
};



#endif // VOXELENGINE_H