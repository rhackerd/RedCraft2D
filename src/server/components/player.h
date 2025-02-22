#ifndef PLAYER_H
#define PLAYER_H

#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class Player
{
private:
    bool initialized;
    boost::uuids::uuid UUID;
    std::string name;

    int uniqueID; // main method for player identification

public:
    Player(boost::uuids::uuid UUID);
    ~Player();

    boost::uuids::uuid getUUID() const {
        return UUID;
    }

    bool operator==(const Player& other) const {
        return UUID == other.UUID;
    }

    std::string getName() const {
        return name;
    }

    void setName(const std::string& name) {
        this->name = name;
    }
};

#endif
