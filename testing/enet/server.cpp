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
                    std::cout << "Received a message: " << (char*)event.packet->data << std::endl;
                    enet_packet_destroy(event.packet);
                    packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
                    
                    // Send the packet to the client
                    for (ENetPeer* peer = server->peers; peer < server->peers + server->peerCount; ++peer) {
                        if (peer->state == ENET_PEER_STATE_CONNECTED) {
                            // Send the packet to the connected client
                            enet_peer_send(peer, 0, packet);
                        }
                    }
                    
                    // Force the immediate sending of the packet
                    enet_host_flush(event.peer->host); // Use the host of the peer to flush
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