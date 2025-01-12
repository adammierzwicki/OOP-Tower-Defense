#include "../inc/game.h"
#include "../inc/logger.h"


int main(int argc, char* argv[]) {
    srand(static_cast<unsigned>(time(0)));

    Logger* logger = Logger::getInstance();
    if (argc > 1) {
        if (std::string(argv[1]) == "-v") {
            logger->setMode(Mode::VERBOSE);
        }
        else {
            logger->setMode(Mode::QUIET);
        }
    }
    else {
        logger->setMode(Mode::QUIET);
    }
    logger->log(LogLevel::DEBUG, "Application started");

    Game game;
    game.startGame();

    logger->log(LogLevel::DEBUG, "Application finished");
    return 0;
}