#include "../inc/game.h"

int main()
{
    srand(static_cast<unsigned>(time(0))); // random seed

    Game game;
    game.startGame();

    return 0;
}