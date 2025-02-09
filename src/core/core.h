#ifndef CORE_H
#define CORE_H

#include <fmt/core.h>
#include "graphics/engine.h"

class Core {
    public:
        Core();
        ~Core();
        void init();
        void event();
        void draw();

        bool shouldCloseWindow() { return graphics.shouldCloseWindow(); }

    private:
        bool debug_voxels;
        bool debug_chunks;
        bool show_fps;
        bool show_player_pos;
        bool show_player_rot;
        bool show_player_chunk;
        bool show_player_voxel;


        engine graphics;
};


#endif