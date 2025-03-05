#ifndef VOXELENGINE_H
#define VOXELENGINE_H
#include "../blocks/blocks.h"
#include "../definitions.h"


#include <vector>
#include <memory>
#include <string>

class VoxelEngine
{
private:
    std::vector<std::unique_ptr<Voxel>> voxels;
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

    std::pair<float, float> getPlayerPosition() { return playerPosition; }
    void setPlayerPosition(std::pair<float, float> position) { playerPosition = position; }
    void setPlayerMoved(bool moved) { playerMoved = moved; }
    bool getPlayerMoved() { return playerMoved; }
    void drawOtherPlayer(std::pair<float, float> position, const char* name);

    void setPlayerName(const char* name) { playerName = name; }
    std::string getPlayerName() { return playerName; }

    void draw();
    void event();
};



#endif // VOXELENGINE_H