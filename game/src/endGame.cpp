#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../inc/endGame.h"

EndGame::EndGame(sf::RenderWindow* window, std::string message) : window(window), selectedItemIndex(1), message(message) {
    if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    if (!backgroundTexture.loadFromFile("textures/starting_background.png")) {
        throw std::runtime_error("Failed to load menu background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);

    const float screenWidth = this->window->getSize().x;
    const float screenHeight = this->window->getSize().y;
    const float yDistance = 150.0f;

    float totalHeight = 2* yDistance;
    float startY = 700;

    sf::Text title;
    title.setFont(font);
    title.setString(message);
    title.setCharacterSize(200);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition((screenWidth - title.getLocalBounds().width) / 2.0f, 50.f);
    this->items.push_back(title);

    sf::Text text;
    text.setFont(font);
    text.setString("Exit");
    text.setCharacterSize(100);

    sf::FloatRect textBounds = text.getLocalBounds();
    float textWidth = textBounds.width;
    float textHeight = textBounds.height;

    text.setPosition((screenWidth - textWidth) / 2.0f, startY);
    text.setOrigin(textBounds.left, textBounds.top + textHeight / 2);
    text.setFillColor(sf::Color::White);
    this->items.push_back(text);
}

EndGame::~EndGame() {}

void EndGame::render() {
    window->clear();
    window->draw(backgroundSprite);
    for (const auto& item : items) {
        window->draw(item);
    }
    window->display();
}

void EndGame::handleInput(bool &isRunning) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            if (items[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                items[selectedItemIndex].setFillColor(sf::Color::White);
                selectedItemIndex = 1;
                items[selectedItemIndex].setFillColor(sf::Color::Green);
                break;
            }
            else {
                items[selectedItemIndex].setFillColor(sf::Color::White);
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (items[selectedItemIndex].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (selectedItemIndex == 1) {
                        bool isRunning = false;
                        this->window->close();
                        return;
                    }
                }
            }
        }
    }
}
