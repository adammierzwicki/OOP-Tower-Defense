#include "../inc/game.h"
#include "../inc/logger.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    Logger* logger = Logger::getInstance();
    logger->setMode(Mode::QUIET);
    logger->log(LogLevel::DEBUG, "Application started");

    Game game;
    game.startGame();

    logger->log(LogLevel::DEBUG, "Application finished");
    return 0;
}