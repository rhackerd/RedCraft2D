#include "game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::draw() {
    voxelengine.event();
    voxelengine.draw();
}