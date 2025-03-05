#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>
#include <utility>
#include <string>
#include <vector>
#include <cstring>
#include "../components/player.hpp"


enum events {
    join
};

class Client
{
private:
    ENetHost* client;
    ENetAddress address;
    ENetPeer* peer;
    ENetEvent event;
    ENetPacket* packet;

    const char* playerName;

    std::vector<std::pair<std::string, std::pair<float, float>>> players;


public:
    Client();
    ~Client();

    void setPlayerName(const char* playerName);

    bool isConnected() { return !(client == nullptr || peer == nullptr || peer->state == ENET_PEER_STATE_DISCONNECTED); }

    void sendPlayerPosition(std::pair<float, float> position);
    void sendPlayerIdentification();

    std::pair<std::string, std::pair<float, float>> recvPlayerPosition(const char* packet);

    void getPlayerInfos(const uint8_t* packet, size_t packetSize);

    uint8_t getEventId(const std::string& packet);

    std::vector<std::pair<std::string, std::pair<float, float>>> getPlayers() { return players; };
    const char* getPlayersName() {return playerName;};
    void init();

    void loop();
};
#endif