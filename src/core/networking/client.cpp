#include "client.hpp"
#include <iostream>
#include "../utils/logging.hpp"
#include <string.h>

Client::Client() : client(nullptr), address(), peer(nullptr), event(), packet(nullptr) {
    if (enet_initialize() != 0) {
        error("failed to initialize enet!");
    }
}

Client::~Client() {
    enet_deinitialize();
}

void Client::init() {
    ENetHost* client = enet_host_create(NULL, 1,2,0,0);

    if(!client) {
        error("failed to create client");
        this->~Client();
        return;
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);
    if (!peer) {
        error("Failed to initiate a connection!");
        enet_host_destroy(client);
        this->~Client();
        return;
    }

    info("attempting to connect to the server at localhost:1234");

    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        info("connected to the server");

        const char* message = "Hello world";


        packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(client);

    }else {
        error("failed to connect to the server");
        enet_peer_reset(peer);
        return;
    }

}