#include "player.h"

Player::Player(boost::uuids::uuid UUID) {
    this->UUID = UUID;
    this->initialized = false;
}

Player::~Player() {

}

