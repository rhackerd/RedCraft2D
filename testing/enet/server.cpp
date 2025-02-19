#include <enet/enet.h>
#include <iostream>
#include <cstring>



int main() {
    if (enet_initialize() != 0) {
        std::cerr << "failed to initialize ENet!" << std::endl;
        return EXIT_FAILURE;
    }

    ENetAddress address;
    ENetHost* server;

    address.host = ENET_HOST_ANY;
    address.port = 1234;

    server = enet_host_create(&address, 32, 2, 0, 0);

    if (!server) {
        std::cerr << "failed to create server!" << std::endl;
        enet_deinitialize();
        return EXIT_FAILURE;
    }

    std::cout << "server started on port 1234" << std::endl;
    const char* message = "Welcome to the server";  // Declare the message outside the switch
    ENetPacket* packet = nullptr; // Declare the packet outside the switch
    while (true) {
        ENetEvent event;
        while (enet_host_service(server, &event, 1000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    std::cout << "A new client connected!" << std::endl;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    if (event.packet->dataLength > 1) {
                        uint8_t eventID = event.packet->data[0];  // Extract event ID
                        const char* receivedPlayerName = reinterpret_cast<const char*>(event.packet->data + 1); // Extract player name

                        std::cout << "Received Event: " << static_cast<int>(eventID) 
                                << ", Player Name: " << receivedPlayerName << std::endl;
                    } else {
                        std::cerr << "Error: Received packet is too small!" << std::endl;
                    }

                    // Destroy the packet after processing
                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "A client disconnected" << std::endl;
                    break;
                default:
                    break;
            }
        }
    }

    enet_host_destroy(server);
    enet_deinitialize();

    return 0;

}