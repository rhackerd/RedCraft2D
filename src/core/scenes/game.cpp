#include "game.h"

Game::Game() {}

Game::~Game() {

}

void Game::draw() {
    voxelengine.event();
    client.loop();


    voxelengine.draw();
}

void Game::init(const char* playerName) {
    client.setPlayerName(playerName);
    client.init();
}