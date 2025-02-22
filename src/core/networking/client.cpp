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
    client = enet_host_create(NULL, 1, 2, 0, 0); // Use the class member client

    if (!client) {
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

    // Use enet_host_service to check for connection within the timeout
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        info("connected to the server");

        uint8_t event_id = events::join;
        size_t playerNameLength = strlen(playerName) + 1;
        size_t packetSize = 1 + playerNameLength;
        char* packetData = new char[packetSize];
        packetData[0] = static_cast<char>(event_id);
        memcpy(packetData + 1, playerName, playerNameLength);

        packet = enet_packet_create(packetData, packetSize, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(client);

        delete[] packetData;
    } else {
        error("failed to connect to the server (timeout or server error)");
        enet_peer_reset(peer);
        return;
    }
}


void Client::setPlayerName(const char* playerName) {
    this->playerName = playerName;
}

void Client::loop() {
    if (client == nullptr || peer == nullptr || peer->state == ENET_PEER_STATE_DISCONNECTED) {
        info("client is not connected");
        return; // The client is disconnected, exit the loop or attempt to reconnect.
    }

    if (enet_host_service(client, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_DISCONNECT:
                info("disconnected from the server");
                // Handle disconnection here, possibly attempt to reconnect.
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // Handle packet reception here
                enet_packet_destroy(event.packet);
                break;
        }
    }
}
