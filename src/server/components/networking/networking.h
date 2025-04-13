#ifndef NETWORKING_H
#define NETWORKING_H

#include <enet/enet.h>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "../player.h"
#include "../../../core/utils/logging.hpp"
#include <thread>
#include <sstream>
#define UUIDT boost::uuids::uuid


class Networking
{
private:
    //enet things
    ENetAddress address;
    ENetHost* server;
    ENetPacket* packet;
    ENetEvent event;

    // server configuration
    int host;
    int port;
    int maxClients;


    // tick things
    int tickCount = 0;


    // players
    std::vector<Player> players;

    // event queue
    std::queue<ENetEvent> eventQueue;
    std::mutex eventMutex;
    std::condition_variable eventCV;

public:
    Networking(int port, int host, int maxClients) : port(port), host(host), maxClients(maxClients) {
        if (enet_initialize() != 0) {
            error("failed to initialize ENet!");
            exit(EXIT_FAILURE);
        }
    }

    ~Networking() {
        enet_host_destroy(server);
        enet_deinitialize();
    }


    // server functions
    void start();
    void stop() {};
    void loop();

    // tick functions
    uint8_t getEventId(const std::string& packet);
    void everyTick();


    // player functions
    boost::uuids::uuid generateUUID(const std::string& ip, uint16_t port);
    int generateUniqueID(boost::uuids::uuid UUID);
    Player* getPlayerByUUID(boost::uuids::uuid UUID);               // get the player by UUID
    Player* getPlayerByPeer(ENetPeer* peer);                        // get the player by peer


    // event functions
    void identifyPlayer(boost::uuids::uuid UUID, std::string name); // adds Player to the player list
    void connectPlayer(boost::uuids::uuid UUID, ENetPeer* peer);    // connects the player and waits for him to identify
    void disconnectPlayer(boost::uuids::uuid UUID);                 // remove the player from the player list if loaded and then disconnect him
    void sendPlayerJoin(Player player, Player toWho);               // send the player join event to all other players
    void sendPlayerLeave(Player player, Player toWho);              // send the player leave event to all other players
    void sendPlayersJoinEvent(Player *player);        // send the player who joined the list of all players joined
    void sendPlayersJoinEventReverse(Player *player);               // send the player who joined the list of all players joined
    void sendPlayersLeaveEvent(Player *player);                     // send the player who left the list of all players joined
    void updatePlayersPosition(Player player, float x, float y);    // update the player position and send it to all other players
    void sendPlayersPositon(Player player,Player playerToSend, float x, float y);   // send the player position to all other players

};


#endif