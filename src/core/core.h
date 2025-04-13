#ifndef CORE_H
#define CORE_H

#include <fmt/core.h>
#include "graphics/engine.h"
#include "scenes/menu.h"
#include "scenes/game.h"


class Core {
    public:
        Core(bool serverMode);
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

        bool serverMode;

        int scene;

        engine graphics;
        Menu menu;
        Game game;
};


#endif