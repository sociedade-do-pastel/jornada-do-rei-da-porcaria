#include "../include/Game.hpp"

int main(int argc, char* argv[])
{
    int a;
    if (argc == 1)
        a = 1;
    else
        a = atoi(argv[1]);

    Game game(a);
    bool success = game.initialize();

    if (success)
        game.runLoop();

    game.shutdown();
    return 0;
}
