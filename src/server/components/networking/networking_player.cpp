#include "networking.h"

Player* Networking::getPlayerByPeer(ENetPeer* peer) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getPeer() == peer) {
            return &players[i];
        }
    }
    return nullptr;
}

UUIDT Networking::generateUUID(const std::string& ip, uint16_t port) {
    std::string data = ip + std::to_string(port);
    boost::uuids::name_generator_md5 gen(boost::uuids::ns::dns());
    return gen(data);
}

Player* Networking::getPlayerByUUID(UUIDT UUID) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getUUID() == UUID) {
            return &players[i];
        }
    }
    return nullptr;
}