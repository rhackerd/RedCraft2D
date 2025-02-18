#ifndef BLOCKS_H
#define BLOCKS_H

class Voxel {
    public:
        virtual void display() const = 0;
        virtual ~Voxel() = default;
};

class Grass : public Voxel {
    public:
        void display() const override {
            
        }
}



#endif