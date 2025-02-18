#include "core.h"

Core::Core() : debug_voxels(false), debug_chunks(false), show_fps(false), show_player_pos(false), show_player_rot(false), show_player_chunk(false), show_player_voxel(false), scene(0) {}


Core::~Core() {
    fmt::print("Shutting down Core\n");
    graphics.deinit();
    fmt::print("Done shutting down Core\n");
}

void Core::init() {
    fmt::print("Initializing Core\n");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    graphics.init();
    graphics.initWindow(800, 600, "Raylib Game");
    fmt::print("Done initializing Core\n");
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
            }
            break;
        case 1:
            game.draw();
            
            break;
    }

    graphics.drawFPS(10, 10);
    graphics.endDrawing();
}