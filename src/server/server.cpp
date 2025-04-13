#include "server.h"
#include <thread>
#include "events.hpp"

void Server::start() {
    networking.start();
}

void Server::stop() {
    networking.stop();
}

void Server::loop() {
    networking.loop();
}