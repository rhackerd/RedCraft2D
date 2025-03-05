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
    void identifyPlayer(boost::uuids::uuid UUID, std::string name); // adds Player to the player list
    void connectPlayer(boost::uuids::uuid UUID, ENetPeer* peer);    // connects the player and waits for him to identify
    void disconnectPlayer(boost::uuids::uuid UUID);                 // remove the player from the player list if loaded and then disconnect him
    Player* getPlayerByUUID(boost::uuids::uuid UUID);               // get the player by UUID
    void sendPlayersPositon(Player player,Player playerToSend, float x, float y);   // send the player position to all other players
    Player* getPlayerByPeer(ENetPeer* peer);                        // get the player by peer
    void updatePlayersPosition(Player player, float x, float y);    // update the player position and send it to all other players
    void sendPlayerJoin(Player player, Player toWho);               // send the player join event to all other players
    void sendPlayerLeave(Player player, Player toWho);              // send the player leave event to all other players
    
    void sendPlayersJoinEvent(Player *player);        // send the player who joined the list of all players joined
    void sendPlayersJoinEventReverse(Player *player);               // send the player who joined the list of all players joined
    void sendPlayersLeaveEvent(Player *player);                     // send the player who left the list of all players joined

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