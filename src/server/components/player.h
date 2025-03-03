#ifndef PLAYER_H
#define PLAYER_H

#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <enet/enet.h>
#include <string>
#include <utility>

class Player
{
private:
    bool initialized;
    boost::uuids::uuid UUID;
    std::string name;

    int uniqueID; // main method for player identification
    ENetPeer* peer;

    std::pair<float, float> position;

public:
    Player(boost::uuids::uuid UUID, ENetPeer* peer) : UUID(UUID), peer(peer) {initialized = false;}
    ~Player() {};
    boost::uuids::uuid getUUID() const {return UUID;}
    bool operator==(const Player& other) const {return UUID == other.UUID;}
    std::string getName() const {return name;}
    void setName(const std::string& name) { this->name = name; }



    void setPeer(ENetPeer* peer) {this->peer = peer;}
    ENetPeer* getPeer() {return peer;}
    int getUniqueID() {return uniqueID;}
    void setUniqueID(int uniqueID) {this->uniqueID = uniqueID;}
    void setPosition(std::pair<float, float> position) {this->position = position;}
    std::pair<float, float> getPosition() {return position;}
    std::pair<float, float> getPosition() const { return position; }
    bool isInitialized() {return initialized;}
    void setInitialized(bool initialized) {this->initialized = initialized;}
};

#endif
