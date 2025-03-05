#include "game.h"
#include "../utils/logging.hpp"

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
    client.loop();


    voxelengine.draw();
    for (auto& player : client.getPlayers()) {
        voxelengine.drawOtherPlayer(player.second, player.first.c_str());
    }
}

void Game::init(const char* playerName) {
    client.setPlayerName(playerName);
    client.init();
    voxelengine.setPlayerName(client.getPlayersName());
}

void Game::onPlayerMove() {
    client.sendPlayerPosition(voxelengine.getPlayerPosition());
}