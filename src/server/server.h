#ifndef SERVER_H
#define SERVER_H

#include <enet/enet.h>
#include <iostream>
#include "../core/utils/logging.hpp"
#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace uuid = boost::uuids;

class Server
{
private:
    ENetAddress address;
    ENetHost* server;
    ENetPacket* packet;
    ENetEvent event;

    int port = 1234;
    int host = ENET_HOST_ANY;

public:
    Server();
    ~Server();

    void start();
    void loop();
    uuid::uuid generateUUID(const std::string& ip, uint16_t port);
    void eventHandler(int eventID, uuid::uuid UUID);


};



#endif