#include "VoxelEngine.h"
#include <iostream>
#include <algorithm> // For std::clamp

void VoxelEngine::event() {
    float deltaTime = GetFrameTime(); // Get time since last frame

    // Acceleration (Movement)
    if (IsKeyDown(KEY_W)) speed.y = std::clamp(speed.y + acceleration * deltaTime, -maxSpeed, maxSpeed);
    if (IsKeyDown(KEY_S)) speed.y = std::clamp(speed.y - acceleration * deltaTime, -maxSpeed, maxSpeed);
    if (IsKeyDown(KEY_A)) speed.x = std::clamp(speed.x + acceleration * deltaTime, -maxSpeed, maxSpeed);
    if (IsKeyDown(KEY_D)) speed.x = std::clamp(speed.x - acceleration * deltaTime, -maxSpeed, maxSpeed);

    // **STRONG Deceleration (Stops Quickly When No Input)**
    float strongFriction = acceleration * decelerationFactor * deltaTime; // 3x acceleration for instant stop

    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
        if (std::abs(speed.y) < strongFriction) speed.y = 0.0f;  // Stop immediately if slow
        else if (speed.y > 0) speed.y -= strongFriction;
        else if (speed.y < 0) speed.y += strongFriction;
    }

    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
        if (std::abs(speed.x) < strongFriction) speed.x = 0.0f;  // Stop immediately if slow
        else if (speed.x > 0) speed.x -= strongFriction;
        else if (speed.x < 0) speed.x += strongFriction;
    }

    // Apply movement
    offset.first += speed.x * deltaTime;
    offset.second += speed.y * deltaTime;
}

void VoxelEngine::draw() {
    for (const auto& voxel : voxels) {
        voxel->display(offset.first, offset.second);
    }
}

VoxelEngine::VoxelEngine() 
    : maxSpeed(250.0f), acceleration(100.0f), offset(0.0f, 0.0f), speed({0.0f, 0.0f}), decelerationFactor(3.0f) {
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            this->voxels.push_back(std::make_unique<Grass>(x * BLOCK_SIZE, y * BLOCK_SIZE));
        }
    }
}

VoxelEngine::~VoxelEngine() {}
