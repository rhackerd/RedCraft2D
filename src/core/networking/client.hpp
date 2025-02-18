#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>

class Client
{
private:
    ENetHost* client;
    ENetAddress address;
    ENetPeer* peer;
    ENetEvent event;
    ENetPacket* packet;


public:
    Client();
    ~Client();

    void init();
};



#endif