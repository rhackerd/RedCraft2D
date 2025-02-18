#include <enet/enet.h>
#include <iostream>
#include <cstring>

int main() {
    if (enet_initialize() != 0) {
        std::cerr << "failed to initialize ENet!" << std::endl;
        return EXIT_FAILURE;
    }

    ENetHost* client = enet_host_create(NULL, 1,2,0,0);

    if (!client) {
        std::cerr << "failed to create client!" << std::endl;
        enet_deinitialize();
        return EXIT_FAILURE;
    }

    ENetAddress address;
    ENetPeer* peer;

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);
    if (!peer) {
        std::cerr << "Failed to initiate connection!" << std::endl;
        enet_host_destroy(client);
        enet_deinitialize();
        return EXIT_FAILURE;
    }

    std::cout  << "Attempting to connect to server..." << std::endl;

    ENetEvent event;
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "connected to server!" << std::endl;

        const char* message = "Hello world";
        ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(client);
    } else {
        std::cerr << "Failed to connect to server!" << std::endl;
        enet_peer_reset(peer);
    }
    while (true) {
        while (enet_host_service(client, &event, 3000) > 0) {
            if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                std::cout << "Recieved message from server: " << (char *)event.packet->data << std::endl;
                enet_packet_destroy(event.packet);
            }
    }
    }

    enet_peer_disconnect(peer, 0);
    enet_host_destroy(client);
    enet_deinitialize();
    return 0;
}