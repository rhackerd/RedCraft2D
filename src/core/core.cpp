#include "core.h"

Core::Core() : debug_voxels(false), debug_chunks(false), show_fps(false), show_player_pos(false), show_player_rot(false), show_player_chunk(false), show_player_voxel(false) {}


Core::~Core() {
    fmt::print("Shutting down Core\n");
    graphics.deinit();
    fmt::print("Done shutting down Core\n");
}

void Core::init() {
    fmt::print("Initializing Core\n");
    graphics.init();
    fmt::print("Done initializing Core\n");
}