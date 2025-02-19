#include "server.h"

Server::Server()
{
    if (enet_initialize() != 0) {
        error("failed to initialize ENet!");
        exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
}

void Server::start() {
    address.host = this->host;
    address.port = this->port;

    server = enet_host_create(&address, 32, 2, 0, 0);

    if (!server) {
        error("failed to create server!");
        enet_deinitialize();
        exit(EXIT_FAILURE);
    }

    info("server started on port 1234");
    ENetPacket* packet = nullptr;
}

void Server::loop() {
    while (enet_host_service(server, &event, 1000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                info("A new client connected! Waiting for him to identify");
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                event.packet;
        }
    }
}

