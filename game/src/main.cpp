#include "../inc/game.h"
#include "../inc/logger.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    Logger* logger = Logger::getInstance();
    logger->setMode(Mode::VERBOSE);
    logger->log(INFO, "Application started");

    Game game;
    game.startGame();

    logger->log(INFO, "Application finished");
    return 0;
}