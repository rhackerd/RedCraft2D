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
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>


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

    int tickCount = 0;


    //threads
    std::thread netThread;
    std::thread gameThread;

    std::queue<ENetEvent> eventQueue;
    std::mutex eventMutex;
    std::condition_variable eventCV;

    std::atomic<bool> running;



public:
    Server();
    ~Server();

    void start();
    void loop();
    void stop();


    //threads
    void networkThreadLoop();
    void gameThreadLoop();


    // players based functions
    void identifyPlayer(boost::uuids::uuid UUID, std::string name);
    void connectPlayer(boost::uuids::uuid UUID, ENetPeer* peer); 
    void disconnectPlayer(boost::uuids::uuid UUID);
    Player* getPlayerByUUID(boost::uuids::uuid UUID);
    void sendPlayersPositon(Player player, float x, float y);
    Player* getPlayerByPeer(ENetPeer* peer);
    void updatePlayersPosition(Player player, float x, float y);
    void sendPlayerJoin(Player player, Player toWho);
    void sendPlayerLeave(Player player, Player toWho);
    

    uint8_t getEventId(const std::string& packet);

    void everyTick();


    // random functions generators
    boost::uuids::uuid generateUUID(const std::string& ip, uint16_t port);
    int generateUniqueID(boost::uuids::uuid UUID);

    bool shouldCloseServer() {
        return shouldClose;
    }
};



#endif