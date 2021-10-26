#include "../include/Game.hpp"

int main()
{
    Game game;
    bool success = game.initialize();

    if (success)
        game.runLoop();

    game.shutdown();
    return 0;
}
