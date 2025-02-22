#include "server.h"

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

void Server::loop() {
    while (enet_host_service(server, &event, 1000) > 0) {
        std::string hostStr = std::to_string(event.peer->address.host);
        uuid::uuid UUID = generateUUID(hostStr, event.peer->address.port);
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                this->connectPlayer(UUID);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                if (event.packet != nullptr && event.packet->data != nullptr) {
                    uint8_t eventID = event.packet->data[0];
                    if (eventID == 0) {
                        // Check if there's enough data for a player name
                        std::string playerName(reinterpret_cast<const char*>(event.packet->data + 1));
                        this->identifyPlayer(UUID, playerName);
                    }
                    enet_packet_destroy(event.packet);
                }
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                this->disconnectPlayer(UUID);
                break;
        }
    }
}


boost::uuids::uuid Server::generateUUID(const std::string& ip, uint16_t port) {
    std::string data = ip + std::to_string(port);
    boost::uuids::name_generator_md5 gen(boost::uuids::ns::dns());
    return gen(data);
}


// player based functions
void Server::connectPlayer(boost::uuids::uuid UUID) {
    info("Player connected with UUID: " + to_string(UUID));
    players.push_back(Player(UUID));
}

void Server::disconnectPlayer(boost::uuids::uuid UUID) {
    Player* player = getPlayerByUUID(UUID);
    if (player != nullptr) {
        players.erase(std::remove(players.begin(), players.end(), *player), players.end());
        info("Player disconnected with UUID: " + to_string(UUID));
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
    if (player != nullptr) {
        player->setName(name);
        info("Player identified with UUID: " + to_string(UUID) + " and name: " + name);
    } else {
        info("Player with UUID " + to_string(UUID) + " not found!");
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