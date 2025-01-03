#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "logger.h"

class Menu {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::RenderWindow* window;

    sf::Font font;
    sf::Text title;
    unsigned int selectedItemIndex;
    std::vector<sf::Text> menuItems;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Logger* logger;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Menu object
     * @param window Game window
     *
     * Create start menu object and initialize all variables
     */
    Menu(sf::RenderWindow* window);

    /**
     * @brief Default destructor
     */
    ~Menu();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get index of selected menu item
     * @return Index of selected menu item
     */
    unsigned int getSelectedItemIndex() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Start menu
     * @return Index of selected menu item
     *
     * Start menu loop
     */
    unsigned int startMenu();

    /**
     * @brief Handle user input
     * @param isRunning Game state
     *
     * Handle user input on menu
     */
    void handleInput(bool& isRunning);

    /**
     * @brief Render menu
     *
     * Display menu on the screen
     */
    void render();

};