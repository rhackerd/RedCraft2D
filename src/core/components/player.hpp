#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// NOTE: Wrote properly

class Player
{
private:
    std::string name;
    std::pair<float, float> position;

public:
    Player(std::string name, float x, float y) : name(name), position({x, y}) {
    }

    ~Player() {}

    std::string getName() const { return name; }
    
    void setName(const std::string& name) { this->name = name; }

    void setPosition(std::pair<float, float> position) { this->position = position; }
    
    std::pair<float, float> getPosition() { return position; }
};

#endif
