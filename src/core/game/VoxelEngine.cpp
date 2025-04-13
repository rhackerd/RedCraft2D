#include "VoxelEngine.h"
#include <algorithm> // For std::clamp
#include <string>    // For std::to_string
#include <cmath>
#include "../utils/logging.hpp"
#include <fmt/core.h>

//NOTE: Not Wrote Properly
// TODO: Rewrite


#define renderRadius 500

// to be honest i dont know what this does 
void VoxelEngine::event() {
    int prevX = playerPosition.first;
    int prevY = playerPosition.second;
    if (windowSizeBeforeResize.first == 0 || windowSizeBeforeResize.second == 0) {
        windowSizeBeforeResize = {GetScreenWidth(), GetScreenHeight()};
        return;
    }
    float deltaWidth = GetScreenWidth() - windowSizeBeforeResize.first;
    float deltaHeight = GetScreenHeight() - windowSizeBeforeResize.second;
    offset.first += deltaWidth / 2.0f;
    offset.second += deltaHeight / 2.0f;
    windowSizeBeforeResize = {GetScreenWidth(), GetScreenHeight()};
    windowSizeBeforeResize = {GetScreenWidth(), GetScreenHeight()};
    fmt::print("offset: {} {}\n", offset.first, offset.second);


    float deltaTime = GetFrameTime();
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D)) direction.x += 1.0f;

    if (direction.x != 0.0f || direction.y != 0.0f) {
        float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
    }

    speed.x = std::clamp(speed.x + direction.x * acceleration * deltaTime, -maxSpeed, maxSpeed);
    speed.y = std::clamp(speed.y + direction.y * acceleration * deltaTime, -maxSpeed, maxSpeed);
    float friction = acceleration * decelerationFactor * deltaTime;
    if (direction.x == 0) speed.x = (std::abs(speed.x) < friction) ? 0.0f : speed.x - std::copysign(friction, speed.x);
    if (direction.y == 0) speed.y = (std::abs(speed.y) < friction) ? 0.0f : speed.y - std::copysign(friction, speed.y);
    camera.target.x += speed.x * deltaTime;
    camera.target.y += speed.y * deltaTime;
    playerPosition = {static_cast<int>(std::round(camera.target.x)), static_cast<int>(std::round(camera.target.y))};
    if (prevX != playerPosition.first || prevY != playerPosition.second) {
        onPlayerMove();
    }

    float centerX = camera.target.x + offset.first;
    float centerY = camera.target.y + offset.second;
    o_terrain.update(centerX, centerY, renderRadius);
}

void VoxelEngine::draw() {
    BeginMode2D(camera);
    

    // draw terrain
    // i was fixing this for like 2h and then i noticed i wasn't compiling the project lol
    int centerX = (GetScreenWidth()/ 2) - offset.first;
    int centerY = (GetScreenHeight()) / 2 - offset.second;

    o_terrain.draw(centerX, centerY);


    EndMode2D();

    // Draw player in the center of the screen
    // draw name
    DrawText(playerName.c_str(), GetScreenWidth() / 2 - 25, GetScreenHeight() / 2 - 50, 20, BLACK);
    DrawRectangle(GetScreenWidth() / 2 - 25, GetScreenHeight() / 2 - 25, 50, 50, RED);
}

VoxelEngine::VoxelEngine() 
    : maxSpeed(250.0f), acceleration(5000.0f), speed({0.0f, 0.0f}), decelerationFactor(3.0f), offset({0.0f, 0.0f}), o_terrain() {
    camera = {0};
    camera.target = {0.0f, 0.0f};
    camera.offset = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    windowSizeBeforeResize = {GetScreenWidth(), GetScreenHeight()};
    
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            o_terrain.addVoxel(std::make_unique<Grass>(x * BLOCK_SIZE, y * BLOCK_SIZE));
        }
    }
}

VoxelEngine::~VoxelEngine() {}

void VoxelEngine::onPlayerMove() {
    this->playerMoved = true;
}

void VoxelEngine::drawOtherPlayer(std::pair<float, float> position, const char* name) {
    if (name == playerName || name == "") return;
    float adjustedX = (position.first - camera.target.x + camera.offset.x) + 375; 
    float adjustedY = (position.second - camera.target.y + camera.offset.y) + 275 ;

    DrawRectangle(adjustedX, adjustedY, 50, 50, BLUE);
    DrawText(name, adjustedX, adjustedY - 20, 20, BLACK);
}
