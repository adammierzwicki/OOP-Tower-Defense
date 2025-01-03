#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../inc/logger.h"

class EndGame {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::RenderWindow* window;

    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    sf::Font font;
    std::string message;
    std::vector<sf::Text> items;
    unsigned int selectedItemIndex;

    Logger* logger;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new EndGame object
     * @param window Game window
     * @param message Message to display
     *
     * Create ending screen object
     */
    EndGame(sf::RenderWindow* window, std::string message);

    /**
     * @brief Default destructor
     */
    ~EndGame();

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Handle user input
     * @param isRunning Game state
     *
     * Handle user input on ending screen
     */
    void handleInput(bool& isRunning);

    /**
     * @brief Render ending screen
     *
     * Update and display ending screen
     */
    void render();
};
