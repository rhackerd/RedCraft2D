#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <enet/enet.h>

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


    


public:
    Client();
    ~Client();

    void setPlayerName(const char* playerName);

    void init();
};



#endif