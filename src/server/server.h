#ifndef SERVER_H
#define SERVER_H

#include <enet/enet.h>
#include "components/player.h"
#include <iostream>
#include "../core/utils/logging.hpp"
#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
#include <random>
#include <sstream>

namespace uuid = boost::uuids;

class Server
{
private:
    ENetAddress address;
    ENetHost* server;
    ENetPacket* packet;
    ENetEvent event;

    std::vector<Player> players;

    int port = 1234;
    int host = ENET_HOST_ANY;

    bool shouldClose = false;

public:
    Server();
    ~Server();

    void start();
    void loop();
    // players based functions
    void identifyPlayer(boost::uuids::uuid UUID, std::string name);
    void connectPlayer(boost::uuids::uuid UUID); 
    void disconnectPlayer(boost::uuids::uuid UUID);
    Player* getPlayerByUUID(boost::uuids::uuid UUID);
    std::string getPlayerName(Player player);


    // random functions generators
    boost::uuids::uuid generateUUID(const std::string& ip, uint16_t port);
    int generateUniqueID(boost::uuids::uuid UUID);

    bool shouldCloseServer() {
        return shouldClose;
    }
};



#endif