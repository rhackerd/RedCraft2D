#include "server.h"
#include <thread>
#include "events.hpp"

#define UUIDT boost::uuids::uuid

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

void Server::stop() {
    enet_host_destroy(server);
    enet_deinitialize();
}

void Server::loop() {
    constexpr int TICK_RATE = 20;  // 20 ticks per second
    constexpr int TICK_TIME_MS = 1000 / TICK_RATE; // 50ms per tick

    auto nextTick = std::chrono::steady_clock::now();

    while (true) {
        // Handle ENet network events (non-blocking)
        while (enet_host_service(server, &event, 0) > 0) {
            std::string hostStr = std::to_string(event.peer->address.host);
            boost::uuids::uuid UUID = generateUUID(hostStr, event.peer->address.port);

            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    this->connectPlayer(UUID, event.peer);
                    this->sendPlayersJoinEvent(getPlayerByUUID(UUID));
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    if (event.packet != nullptr && event.packet->data != nullptr) {
                        uint8_t eventID = getEventId(reinterpret_cast<const char*>(event.packet->data));
                        if (eventID == eventIdentify) {
                            std::string playerName(reinterpret_cast<const char*>(event.packet->data + 1));
                            this->identifyPlayer(UUID, playerName);
                        }else if(eventID == eventMove) {
                            // Player moved
                            Player* player = getPlayerByUUID(UUID);
                            if (player != nullptr) {
                                float x = *reinterpret_cast<float*>(event.packet->data + 1);
                                float y = *reinterpret_cast<float*>(event.packet->data + 5);
                                updatePlayersPosition(*player, x, y);
                            }
                        }
                        enet_packet_destroy(event.packet);
                    }
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    this->disconnectPlayer(UUID);
                    break;
            }
        }

        // Run game logic every tick
        tickCount++;
        //updateGame(tickCount);

        everyTick();

        // Sleep until the next tick
        nextTick += std::chrono::milliseconds(TICK_TIME_MS);
        std::this_thread::sleep_until(nextTick);
    }
}

void Server::everyTick() {
    
}

uint8_t Server::getEventId(const std::string& packet) {
    return static_cast<uint8_t>(packet[0]);
}



boost::uuids::uuid Server::generateUUID(const std::string& ip, uint16_t port) {
    std::string data = ip + std::to_string(port);
    boost::uuids::name_generator_md5 gen(boost::uuids::ns::dns());
    return gen(data);
}


// player based functions
void Server::connectPlayer(boost::uuids::uuid UUID, ENetPeer* peer) {
    players.push_back(Player(UUID, peer));
}

void Server::disconnectPlayer(boost::uuids::uuid UUID) {
    Player* player = getPlayerByUUID(UUID);
    if (player != nullptr) {
        players.erase(std::remove(players.begin(), players.end(), *player), players.end());
        info("Player " + player->getName() + " disconnected");
    } else {
        info("Player with UUID " + to_string(UUID) + " not found!");
    }
}


Player* Server::getPlayerByUUID(boost::uuids::uuid UUID) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getUUID() == UUID) {
            return &players[i];
        }
    }
    return nullptr; // Return nullptr if no player found
}

void Server::identifyPlayer(boost::uuids::uuid UUID, std::string name) {
    Player* player = getPlayerByUUID(UUID);
    if (player == nullptr) {
        info("Player with UUID " + to_string(UUID) + " not found!");
        return;
    }

    player->setName(name);
    info("Player identified with name: " + name);

    sendPlayersJoinEvent(player);
}

void Server::sendPlayersJoinEvent(Player *player) {
    UUIDT UUID = player->getUUID();
    for (auto p : players) {
        if (!(p == *player)) {
            sendPlayerJoin(*player, p);
        }
    }
}

int Server::generateUniqueID(boost::uuids::uuid UUID) {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::stringstream ss;
    ss << duration << UUID; 
    std::string combinedString = ss.str();
    int uniqueID = 0;
    for (size_t i = 0; i < 5 && i < combinedString.size(); ++i) {uniqueID = uniqueID * 10 + (combinedString[i] - '0');}
    return uniqueID % 100000;
}

void Server::updatePlayersPosition(Player player, float x, float y) {
    player.setPosition({x,y});

    for (int i = 0; i < players.size(); i++) {
        if (players[i].getUUID() != player.getUUID()) {
            sendPlayersPositon(players[i], player, x,y);
        }
    }
}

Player* Server::getPlayerByPeer(ENetPeer* peer) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getPeer() == peer) {
            return &players[i];
        }
    }
    return nullptr;
}

void Server::sendPlayersPositon(Player player,Player playerToSend, float x, float y) {
    if (player.getPeer() != nullptr) {
        // Get the player's name
        std::string playerName = playerToSend.getName();

        // Calculate the size of the packet (1 byte for event type + size of name + size of position)
        size_t packetSize = 1 + sizeof(uint16_t) + playerName.size() + sizeof(x) + sizeof(y);
        
        uint8_t* data = new uint8_t[packetSize];

        data[0] = eventMove;  // Move event (001)

        // Copy the name length (2 bytes for uint16_t)
        uint16_t nameLength = playerName.size();
        std::memcpy(data + 1, &nameLength, sizeof(nameLength));

        // Copy the player's name
        std::memcpy(data + 3, playerName.c_str(), playerName.size());

        // Copy the x and y position
        std::memcpy(data + 3 + playerName.size(), &x, sizeof(x));
        std::memcpy(data + 3 + playerName.size() + sizeof(x), &y, sizeof(y));

        // Create the packet and send it
        ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(player.getPeer(), 0, packet);

        // Clean up dynamically allocated memory
        delete[] data;
    }
}


void Server::sendPlayerJoin(Player player, Player toWho) {
    // make it as 002, playername, x, y
    std::string playerName = player.getName();
    uint16_t nameLength = playerName.size();
    size_t packetSize = 1 + sizeof(nameLength) + nameLength + sizeof(float) + sizeof(float);
    uint8_t* data = new uint8_t[packetSize];

    data[0] = eventJoin;  // Join event (002)

    size_t offset = 1;
    std::memcpy(data + offset, &nameLength, sizeof(nameLength));
    offset += sizeof(nameLength);

    std::memcpy(data + offset, playerName.c_str(), nameLength);
    offset += nameLength;

    std::pair<float, float> position = player.getPosition();
    std::memcpy(data + offset, &position.first, sizeof(float));
    offset += sizeof(float);
    std::memcpy(data + offset, &position.second, sizeof(float));

    ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(toWho.getPeer(), 0, packet);
}