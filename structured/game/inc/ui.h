#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "windowHandler.h"

class UI {
private:
    sf::Font font;
    WindowHandler* windowHandler;

    sf::Text roundDisplay;
    sf::Text healthDisplay;
    sf::Text moneyDisplay;

    std::vector<sf::Text> buttons;
    int selectedButtonIndex;

public:
    UI(WindowHandler* windowHandler);
    ~UI();

    void render();
    void handleInput();
    void setRoundText(int round);
    void setHealthText(int health);
    void setMoneyText(int money);
    int getSelectedButton() const;
    void startUI();
};