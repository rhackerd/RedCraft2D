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


#include "components/networking/networking.h"


namespace uuid = boost::uuids;

class Server
{
private:

    bool shouldClose = false;


    Networking networking;


public:
    Server(int port, int host, int maxClients) : networking(port, host, maxClients) {
    }


    ~Server() {};

    void start();
    void loop();
    void stop();
    


    // random functions generators

    bool shouldCloseServer() {
        return shouldClose;
    }
};

#endif