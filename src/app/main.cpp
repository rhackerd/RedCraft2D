#include <fmt/core.h>
#include "core.h"
#include "args.h"

int main(int argc, char* argv[]) {
    bool serverMode = false;
    
    Args args(argc, argv);

    int port = args.getArgInt("port", 1234);
    int maxClients = args.getArgInt("clients", 16);
    if (args.isArg("server")) serverMode = true;
    if (args.isArg("help")) {fmt::print("Usage: ./game [--server]\n");return 0;}



    if (serverMode) {
        fmt::print("Server is removed for testing purposes\n");
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