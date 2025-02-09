#include <fmt/core.h>
#include "core.h"

int main() {
    Core game;
    game.init();
    while (!game.shouldCloseWindow()) {
        game.event();
        game.draw();
    }
    return 0;
}