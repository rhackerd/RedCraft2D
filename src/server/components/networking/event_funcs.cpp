// void identifyPlayer(boost::uuids::uuid UUID, std::string name); // adds Player to the player list
// void connectPlayer(boost::uuids::uuid UUID, ENetPeer* peer);    // connects the player and waits for him to identify
// void disconnectPlayer(boost::uuids::uuid UUID);                 // remove the player from the player list if loaded and then disconnect him
// void sendPlayerJoin(Player player, Player toWho);               // send the player join event to all other players
// void sendPlayerLeave(Player player, Player toWho);              // send the player leave event to all other players
// void sendPlayersJoinEvent(Player *player);        // send the player who joined the list of all players joined
// void sendPlayersJoinEventReverse(Player *player);               // send the player who joined the list of all players joined
// void sendPlayersLeaveEvent(Player *player);                     // send the player who left the list of all players joined
// void updatePlayersPosition(Player player, float x, float y);    // update the player position and send it to all other players
// void sendPlayersPositon(Player player,Player playerToSend, float x, float y);   // send the player position to all other players

#include "networking.h"
#include "../../events.hpp"




void Networking::sendPlayerJoin(Player player, Player toWho) {
    info("Sending join event to " + toWho.getName() + " for player " + player.getName());
    std::string playerName = player.getName();
    uint16_t nameLength = playerName.size();
    size_t packetSize = 1 + sizeof(nameLength) + nameLength + sizeof(float) + sizeof(float);
    uint8_t* data = new uint8_t[packetSize];

    data[0] = eventJoin;  // Join event (002)

    size_t offset = 1;
    std::memcpy(data + offset, &nameLength, sizeof(nameLength));
    offset += sizeof(nameLength);

    std::memcpy(data + offset, playerName.c_str(), nameLength);
    offset += nameLength;

    std::pair<float, float> position = player.getPosition();
    std::memcpy(data + offset, &position.first, sizeof(float));
    offset += sizeof(float);
    std::memcpy(data + offset, &position.second, sizeof(float));

    ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(toWho.getPeer(), 0, packet);
}

void Networking::sendPlayersPositon(Player player,Player playerToSend, float x, float y) {
    info("Sending position event to " + playerToSend.getName() + " for player " + player.getName());
    if (player.getPeer() != nullptr) {
        std::string playerName = playerToSend.getName();

        size_t packetSize = 1 + sizeof(uint16_t) + playerName.size() + sizeof(x) + sizeof(y);
        
        uint8_t* data = new uint8_t[packetSize];

        data[0] = eventMove;  // Move event (001)


        uint16_t nameLength = playerName.size();
        std::memcpy(data + 1, &nameLength, sizeof(nameLength));
        std::memcpy(data + 3, playerName.c_str(), playerName.size());
        std::memcpy(data + 3 + playerName.size(), &x, sizeof(x));
        std::memcpy(data + 3 + playerName.size() + sizeof(x), &y, sizeof(y));

        ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(player.getPeer(), 0, packet);

        delete[] data;
    }
}

void Networking::updatePlayersPosition(Player player, float x, float y) {
    info("Updating position of player " + player.getName() + " to x: " + std::to_string(x) + " y: " + std::to_string(y));
    player.setPosition({x,y});

    for (int i = 0; i < players.size(); i++) {
        if (players[i].getUUID() != player.getUUID()) {
            sendPlayersPositon(players[i], player, x,y);
        }
    }
}

void Networking::sendPlayerLeave(Player player, Player toWho) {
    info("Sending leave event to " + toWho.getName() + " for player " + player.getName());
    std::string playerName = player.getName();
    info("Sending leave event to " + toWho.getName() + " for player " + playerName);
    size_t packetSize = 1 + sizeof(uint16_t) + playerName.size();
    uint8_t* data = new uint8_t[packetSize];

    data[0] = eventLeave;  // Leave event (003)

    size_t offset = 1;
    uint16_t nameSize = playerName.size();
    std::memcpy(data + offset, &nameSize, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    std::memcpy(data + offset, playerName.c_str(), playerName.size());

    ENetPacket* packet = enet_packet_create(data, packetSize, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(toWho.getPeer(), 0, packet);
}

void Networking::sendPlayersLeaveEvent(Player *player) {
    info("Sending leave event to all players for player " + player->getName());
    for (auto p : players) {
        if (!(p == *player)) {
            info("Sending leave event to " + p.getName());
            sendPlayerLeave(*player, p);
        }
    }
}

void Networking::sendPlayersJoinEvent(Player *player) {
    info("Sending join event to all players for player " + player->getName());

}

uint8_t Networking::getEventId(const std::string& packet) {
    info("Getting event ID from packet");
    return static_cast<uint8_t>(packet[0]);
}

void Networking::connectPlayer(UUIDT UUID, ENetPeer* peer) {
    info("Player connected with UUID " + to_string(UUID));
    players.push_back(Player(UUID, peer));
}

void Networking::disconnectPlayer(UUIDT UUID) {
    info("Player disconnected with UUID " + to_string(UUID));
    Player* player = getPlayerByUUID(UUID);
    if (player != nullptr) {
        players.erase(std::remove(players.begin(), players.end(), *player), players.end());
        info("Player " + player->getName() + " disconnected");
    } else {
        info("Player with UUID " + to_string(UUID) + " not found!");
    }
}

void Networking::identifyPlayer(UUIDT UUID, std::string name) {
    info("Identifying player with UUID " + to_string(UUID) + " with name " + name);
    Player* player = getPlayerByUUID(UUID);
    if (player == nullptr) {
        info("Player with UUID " + to_string(UUID) + " not found!");
        return;
    }

    player->setName(name);
    info("Player identified with name: " + name);

    sendPlayersJoinEvent(player);
}

void Networking::sendPlayersJoinEventReverse(Player *player) {
    info("Sending join event to all players for player " + player->getName());
    UUIDT UUID = player->getUUID();
    for (auto p : players) {
        if (!(p == *player)) {
            sendPlayerJoin(p, *player);
        }
    }
}