#include <fmt/core.h>
#include "core.h"
#include "../../src/server/server.h"

int main(int argc, char* argv[]) {
    bool serverMode = false;
    

    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-server") == 0) {
            serverMode = true;
        }
    }

    if (serverMode) {
        Server server;
        server.start();
        while (true) {
            server.loop();
        }
    }else{
        Core game(false);
        game.init();
        while (!game.shouldCloseWindow()) {
            game.event();
            game.draw();
        }
    }
    return 0;
}