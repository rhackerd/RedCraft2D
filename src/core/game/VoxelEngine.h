#ifndef VOXELENGINE_H
#define VOXELENGINE_H
#include "../blocks/blocks.h"
#include "../definitions.h"


#include <vector>
#include <memory>

class VoxelEngine
{
private:
    std::vector<std::unique_ptr<Voxel>> voxels;
    std::pair<float, float> offset;

    Vector2 speed;

    float maxSpeed;
    float acceleration;
    float decelerationFactor;


public:
    VoxelEngine();
    ~VoxelEngine();

    void draw();
    void event();
};



#endif // VOXELENGINE_H