#include "core.h"
#include "utils/logging.hpp"

Core::Core(bool serverMode) : debug_voxels(false), debug_chunks(false), show_fps(false), show_player_pos(false), show_player_rot(false), show_player_chunk(false), show_player_voxel(false), scene(0), serverMode(serverMode) {}


Core::~Core() {
    info("Shutting down Core");
    graphics.deinit();
    info("Done shutting down Core");
}

void Core::init() {
    info("Initializing Core");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    graphics.init();
    graphics.initWindow(800, 600, "Raylib Game");
    info("Done initializing Core");
}

void Core::event() {

}

void Core::draw() {
    graphics.beginDrawing();
    graphics.clearBackground(RAYWHITE);

    switch (scene) {
        case 0:
            menu.draw();
            if (menu.getNext()) {
                scene += 1;
                game.init();
            }
            break;
        case 1:
            game.draw();
            
            break;
    }

    graphics.drawFPS(10, 10);
    graphics.endDrawing();
}