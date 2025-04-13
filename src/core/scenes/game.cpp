#include "game.h"
#include "../utils/logging.hpp"

// NOTE: Half-Wrote properly
// TODO: Rewrite

Game::Game() {
}

Game::~Game() {

}

void Game::event() {
    if (voxelengine.getPlayerMoved()) {
        this->onPlayerMove();
        voxelengine.setPlayerMoved(false);
    }
}

void Game::draw() {
    this->event();

    voxelengine.event();


    voxelengine.draw();
}

void Game::init(const char* playerName) {
    voxelengine.setPlayerName(playerName);
}

void Game::onPlayerMove() {
}