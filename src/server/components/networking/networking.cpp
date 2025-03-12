#include "networking.h"
#include "../../events.hpp"


void Networking::start() {
    address.host = host;
    address.port = port;

    server = enet_host_create(&address, 32, maxClients, 0, 0);

    if (!server) {
        error("failed to create server!");
        enet_deinitialize();
        exit(EXIT_FAILURE);
    }

    info("server started on port " + std::to_string(port));
    ENetPacket* packet = nullptr;
}


void Networking::loop() {
    constexpr int TICK_RATE = 20;  // 20 ticks per second
    constexpr int TICK_TIME_MS = 1000 / TICK_RATE; // 50ms per tick

    auto nextTick = std::chrono::steady_clock::now();

    while (true) {
        // Handle ENet network events (non-blocking)
        while (enet_host_service(server, &event, 0) > 0) {
            std::string hostStr = std::to_string(event.peer->address.host);
            boost::uuids::uuid UUID = generateUUID(hostStr, event.peer->address.port);

            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    this->connectPlayer(UUID, event.peer);
                    this->sendPlayersJoinEventReverse(getPlayerByUUID(UUID));
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    if (event.packet != nullptr && event.packet->data != nullptr) {
                        uint8_t eventID = getEventId(reinterpret_cast<const char*>(event.packet->data));
                        if (eventID == eventIdentify) {
                            std::string playerName(reinterpret_cast<const char*>(event.packet->data + 1));
                            this->identifyPlayer(UUID, playerName);
                        }else if(eventID == eventMove) {
                            // Player moved
                            Player* player = getPlayerByUUID(UUID);
                            if (player != nullptr) {
                                float x = *reinterpret_cast<float*>(event.packet->data + 1);
                                float y = *reinterpret_cast<float*>(event.packet->data + 5);
                                updatePlayersPosition(*player, x, y);
                            }
                        }
                        enet_packet_destroy(event.packet);
                    }
                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    this->sendPlayersLeaveEvent(getPlayerByUUID(UUID));
                    this->disconnectPlayer(UUID);
                    break;
            }
        }

        // Run game logic every tick
        tickCount++;
        //updateGame(tickCount);

        everyTick();

        // Sleep until the next tick
        nextTick += std::chrono::milliseconds(TICK_TIME_MS);
        std::this_thread::sleep_until(nextTick);
    }
}

int Networking::generateUniqueID(boost::uuids::uuid UUID) {
    info("Generating unique ID for player " + boost::uuids::to_string(UUID));
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::stringstream ss;
    ss << duration << UUID; 
    std::string combinedString = ss.str();
    int uniqueID = 0;
    for (size_t i = 0; i < 5 && i < combinedString.size(); ++i) {uniqueID = uniqueID * 10 + (combinedString[i] - '0');}
    return uniqueID % 100000;
}

void Networking::everyTick() {

}