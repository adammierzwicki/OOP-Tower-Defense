#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class UI {
private:
    sf::Font font;
    sf::RenderWindow* window;
    // std::vector<sf::Text> buttons;

    // sf::Texture backgroundTexture;
    // sf::Sprite backgroundSprite;

    sf::Text gunType1Button;
    sf::Text gunType2Button;
    sf::Text gunType3Button;
    sf::Text startGameButton;

    sf::Text roundDisplay;
    sf::Text healthDisplay;
    sf::Text moneyDisplay;

    int selectedButtonIndex;

public:
    UI(sf::RenderWindow* window);
    ~UI();

    void render();
    void handleInput();
    void setRoundText(int round);
    void setHealthText(int health);
    void setMoneyText(int money);
    int getSelectedButton() const;
    void startUI();
};