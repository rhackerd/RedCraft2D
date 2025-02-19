#include "game.h"

Game::Game() {}

Game::~Game() {

}

void Game::draw() {
    voxelengine.event();


    voxelengine.draw();
}

void Game::init(const char* playerName) {
    client.setPlayerName(playerName);
    client.init();
}