#include "../include/Game.hpp"

int main(int argc, char *argv[])
{
    Game game(atoi(argv[1]));
    bool success = game.initialize();

    if (success)
        game.runLoop();

    game.shutdown();
    return 0;
}
