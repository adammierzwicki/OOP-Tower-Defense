#include "../inc/endGame.h"

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>


//-----------------------------------
//     Constructor and destructor
//-----------------------------------

EndGame::EndGame(sf::RenderWindow* window, std::string message) : window(window), message(message) {
    this->logger = Logger::getInstance();

    if (!this->font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load font (\"./fonts/BoldKei-nRAWP.ttf\")", "EndGame::EndGame", __LINE__);
        throw std::runtime_error("Failed to load font");
    }
    if (!this->backgroundTexture.loadFromFile("textures/starting_background.png")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load menu background texture (\"./textures/starting_background.png\")", "EndGame::EndGame", __LINE__);
        throw std::runtime_error("Failed to load menu background texture");
    }
    this->backgroundSprite.setTexture(this->backgroundTexture);

    const float screenWidth = this->window->getSize().x;
    const float startY = 700;

    sf::Text title;
    title.setFont(this->font);
    title.setString(this->message);
    title.setCharacterSize(250);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(7);
    title.setPosition((screenWidth - title.getLocalBounds().width) / 2.f, 20.f);
    this->items.push_back(title);

    sf::Text text;
    text.setFont(this->font);
    text.setString("Exit");
    text.setCharacterSize(150);

    const sf::FloatRect textBounds = text.getLocalBounds();
    const float textWidth = textBounds.width;
    const float textHeight = textBounds.height;

    text.setPosition((screenWidth - textWidth) / 2.f, startY);
    text.setOrigin(textBounds.left, textBounds.top + textHeight / 2.f);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(5);
    this->items.push_back(text);

    this->selectedItemIndex = 1;
}

EndGame::~EndGame() {}

//-----------------------------------
//          Public methods
//-----------------------------------

void EndGame::handleInput(bool& isRunning) {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            if (this->items[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                this->items[this->selectedItemIndex].setFillColor(sf::Color::White);
                this->selectedItemIndex = 1;
                this->items[this->selectedItemIndex].setFillColor(sf::Color::Red);
                break;
            }
            else {
                this->items[this->selectedItemIndex].setFillColor(sf::Color::White);
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
                if (this->items[this->selectedItemIndex].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (this->selectedItemIndex == 1) {
                        isRunning = false;
                        return;
                    }
                }
            }
        }
    }
}

void EndGame::render() {
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    for (const auto& item : this->items) {
        this->window->draw(item);
    }
    this->window->display();
}