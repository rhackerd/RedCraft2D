#include "client.hpp"
#include <iostream>
#include "../utils/logging.hpp"
#include <cstring>
#include "../../server/events.hpp"


Client::Client() : client(nullptr), address(), peer(nullptr), event(), packet(nullptr) {
    if (enet_initialize() != 0) {
        error("failed to initialize enet!");
    }
}

Client::~Client() {
    enet_peer_disconnect(peer, 0);
    enet_host_flush(client);
    enet_host_destroy(client);
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

        this->sendPlayerIdentification();

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
                uint8_t eventId = getEventId(reinterpret_cast<char*>(event.packet->data));
                if (eventId==eventIdentify) {

                }else if(eventId==eventMove) {
                    std::pair<std::string, std::pair<float, float>> playerData = recvPlayerPosition(reinterpret_cast<char*>(event.packet->data));
                    std::string playerName = playerData.first;
                    std::pair<float, float> position = playerData.second;
                    for (auto& player : players) {
                        if (player.first == playerName) {
                            player.second = position;
                    
                            break;
                        }
                    }
                }else if(eventId==eventJoin) {
                    this->getPlayerInfos(reinterpret_cast<uint8_t*>(event.packet->data), event.packet->dataLength);
                }else if(eventId==eventLeave) {
                    // Handle player leaving
                    // 3, playername
                    std::string playerName(reinterpret_cast<char*>(event.packet->data + 1));
                    info("Player left: " + playerName);
                    for (auto it = players.begin(); it != players.end(); ++it) {
                        if (it->first == playerName) {
                            players.erase(it);
                            break;
                        }
                    }
                }
                else {
                    info("received unknown event: " + std::to_string(eventId));
                }

                enet_packet_destroy(event.packet);
                break;
        }
    }
}



void Client::sendPlayerPosition(std::pair<float, float> position) {
    if (isConnected()) {
        size_t packetSize = 1 + sizeof(position);
        uint8_t* data = new uint8_t[packetSize];

        data[0] = eventMove;  // Move event (001)

        std::memcpy(data + 1, &position, sizeof(position));

        ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);

        delete[] data;
    }
}


void Client::sendPlayerIdentification() {
    uint8_t event_id = eventIdentify;  // Identify event (000)
    size_t playerNameLength = strlen(playerName) + 1;
    size_t packetSize = 1 + playerNameLength;
    char* packetData = new char[packetSize];

    packetData[0] = static_cast<char>(event_id);

    memcpy(packetData + 1, playerName, playerNameLength);

    ENetPacket* packet = enet_packet_create(packetData, packetSize, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);

    delete[] packetData;
}

uint8_t Client::getEventId(const std::string& packet) {
    return static_cast<uint8_t>(packet[0]);
}

std::pair<std::string, std::pair<float, float>> Client::recvPlayerPosition(const char* packet) {
    size_t offset = 0;

    // First byte is the event type, let's skip it
    uint8_t eventType = packet[offset];
    offset++;

    if (eventType != eventMove) {
        // If this is not a move event, return an empty pair
        return {"", {0.0f, 0.0f}};
    }

    // Read the name length (2 bytes)
    uint16_t nameLength;
    std::memcpy(&nameLength, packet + offset, sizeof(nameLength));
    offset += sizeof(nameLength);

    // Read the player name (variable length)
    std::string playerName(reinterpret_cast<const char*>(packet + offset), nameLength);
    offset += nameLength;

    // Read the x and y position (2 floats: x, y)
    float x, y;
    std::memcpy(&x, packet + offset, sizeof(float));
    offset += sizeof(float);
    std::memcpy(&y, packet + offset, sizeof(float));
    offset += sizeof(float);

    // Return a pair with player name and position
    return {playerName, {x, y}};
}


void Client::getPlayerInfos(const uint8_t* packet, size_t packetLength) {

    // Read the event type (first byte)
    uint8_t eventType = packet[0];
    if (eventType != eventJoin) return;  // Ensure it's the "Join" event (eventJoin = 2)

    size_t offset = 1;  // Start after the event type byte

    // Read name length (2 bytes)
    if (offset + sizeof(uint16_t) > packetLength) return;
    uint16_t nameLength;
    std::memcpy(&nameLength, packet + offset, sizeof(nameLength));
    offset += sizeof(nameLength);

    // Read player name (variable length)
    if (offset + nameLength > packetLength) return;
    std::string playerName(reinterpret_cast<const char*>(packet + offset), nameLength);
    offset += nameLength;

    // Read player position (2 floats: x, y)
    if (offset + 2 * sizeof(float) > packetLength) return;
    float x, y;
    std::memcpy(&x, packet + offset, sizeof(float));
    offset += sizeof(float);
    std::memcpy(&y, packet + offset, sizeof(float));
    offset += sizeof(float);
    
    players.push_back(std::make_pair(playerName, std::make_pair(x, y)));

    // Print received player data
    info("Player joined: " + playerName + " at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
}


