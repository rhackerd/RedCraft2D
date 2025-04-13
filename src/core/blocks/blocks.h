#ifndef BLOCKS_H
#define BLOCKS_H

#include <raylib.h>
#include "../definitions.h"

class Voxel {
    protected:
        int x,y;

    public:
        Voxel(int x = 0, int y = 0): x(x), y(y) {}

        virtual void display(int x, int y) const = 0;
        virtual ~Voxel() = default;

        void changePosition(int x, int y) {
            this->x = x;this->y = y;
        }

        int getX() const {return x;}
        int getY() const {return y;}
};

class Grass : public Voxel {
    public:
        using Voxel::Voxel;

        void display(int x, int y) const override {
            DrawRectangle(this->x+x,this->y+y,BLOCK_SIZE,BLOCK_SIZE,GREEN);
        }
};



#endif