#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "windowHandler.h"
#include "logger.h"

enum class ButtonType {
    MACHINE_GUN = 1,
    HIGH_DAMAGE_GUN = 2,
    SNIPER_RIFLE = 3,
    START_GAME = 4,
    UPGRADE = 5,
    NONE = 0
};

struct Button {
    sf::RectangleShape rectangle;
    sf::Text nameText;
    sf::Text priceText;
};

class WindowHandler;

/**
 * @brief Class for handling UI elements
 *
 * Contains methods for rendering and handling UI elements
 */
class UI {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    WindowHandler* windowHandler;

    sf::Font font;
    sf::Text roundDisplay;
    sf::Text healthDisplay;
    sf::Text moneyDisplay;

    std::vector<Button> buttons;
    int selectedButtonIndex;

    Logger* logger;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new UI object
     * @param windowHandler Window handler object
     *
     * Initialize UI object
     */
    UI(WindowHandler* windowHandler);

    /**
     * @brief Default destructor
     */
    ~UI();
    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get selected button index
     * @return Selected button index
     */
    int getSelectedButton() const;

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set displayed round
     * @param round Round number
     */
    void setRoundText(int round);

    /**
     * @brief Set displayed health
     * @param health Player health
     */
    void setHealthText(int health);

    /**
     * @brief Set displayed money
     * @param money Player money
     */
    void setMoneyText(int money);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Render UI
     *
     * Render UI elements on screen
     */
    void render();

    /**
     * @brief Handle input
     * @return ButtonType Selected button
     *
     * Handle user interaction with UI
     */
    ButtonType handleInput();
};