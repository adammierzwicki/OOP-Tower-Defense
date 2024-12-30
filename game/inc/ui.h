#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "windowHandler.h"
class WindowHandler;
enum class ButtonType;
struct Button {
    sf::RectangleShape rectangle;
    sf::Text nameText;
    sf::Text priceText;
};

class UI {
private:
    sf::Font font;
    WindowHandler* windowHandler;

    sf::Text roundDisplay;
    sf::Text healthDisplay;
    sf::Text moneyDisplay;

    std::vector<Button> buttons;
    int selectedButtonIndex;

public:
    UI(WindowHandler* windowHandler);
    ~UI();

    void render();
    ButtonType handleInput();
    void setRoundText(int round);
    void setHealthText(int health);
    void setMoneyText(int money);
    int getSelectedButton() const;
};

enum class ButtonType {
    MACHINE_GUN = 1,
    HIGH_DAMAGE_GUN = 2,
    SNIPER_RIFLE = 3,
    START_GAME = 4,
    UPGRADE = 5,
    NONE = 0
};


