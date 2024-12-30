#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../inc/menu.h"

Menu::Menu(sf::RenderWindow* window) : window(window), selectedItemIndex(0) {
    if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    std::vector<std::string> items = {"Start Game", "Exit"};

    if (!backgroundTexture.loadFromFile("textures/starting_background.png")) {
        throw std::runtime_error("Failed to load menu background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);

    const float screenWidth = this->window->getSize().x;
    const float screenHeight = this->window->getSize().y;
    const float yDistance = 150.0f;

    float totalMenuHeight = items.size() * yDistance;
    float startY = (screenHeight - totalMenuHeight) / 2.0f + 100.f;

    this->title.setFont(font);
    this->title.setString("Tower Defense");
    this->title.setCharacterSize(200);
    this->title.setFillColor(sf::Color::Yellow);
    this->title.setStyle(sf::Text::Bold);
    this->title.setPosition((screenWidth - title.getLocalBounds().width) / 2.0f, 50.f);

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(100);

        sf::FloatRect textBounds = text.getLocalBounds();
        float textWidth = textBounds.width;
        float textHeight = textBounds.height;

        text.setPosition((screenWidth - textWidth) / 2.0f, startY + i * yDistance);
        text.setOrigin(textBounds.left, textBounds.top + textHeight / 2);
        if (i == 0) {
            text.setFillColor(sf::Color::Green);
        } else {
            text.setFillColor(sf::Color::White);
        }
        menuItems.push_back(text);
    }
}

Menu::~Menu() {}

int Menu::startMenu() {
    bool isRunning = true;

    while (isRunning && window->isOpen()) {
        handleInput(isRunning);
        render();
    }
    return selectedItemIndex;
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}

void Menu::render() {
    window->clear();
    window->draw(backgroundSprite);
    window->draw(title);
    for (const auto& item : menuItems) {
        window->draw(item);
    }
    window->display();
}

void Menu::handleInput(bool &isRunning) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            for (size_t i = 0; i < menuItems.size(); ++i) {
                if (menuItems[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    menuItems[selectedItemIndex].setFillColor(sf::Color::White);
                    selectedItemIndex = i;
                    menuItems[selectedItemIndex].setFillColor(sf::Color::Green);
                    break;
                }
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (menuItems[selectedItemIndex].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (selectedItemIndex == 0) {
                        isRunning = false;
                    } else if (selectedItemIndex == 1) {
                        window->close();
                    }
                }
            }
        }
    }
}
