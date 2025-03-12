#ifndef POSITION_H
#define POSITION_H
#include "vectors.h"

class Position
{
private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

public:
    Position();
    ~Position();
};

Position::Position()
{
}

Position::~Position()
{
}



#endif