#include "../inc/menu.h"

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Menu::Menu(sf::RenderWindow* window) : window(window), selectedItemIndex(0) {
    this->logger = Logger::getInstance();

    if (!this->font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load font (\"./fonts/BoldKei-nRAWP.ttf\")", "Menu::Menu()", __LINE__);
        throw std::runtime_error("Failed to load font");
    }

    if (!this->backgroundTexture.loadFromFile("textures/starting_background.png")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load menu background texture (\"./textures/starting_background.png\")", "Menu::Menu()", __LINE__);
        throw std::runtime_error("Failed to load menu background texture");
    }
    this->backgroundSprite.setTexture(this->backgroundTexture);

    const float screenWidth = this->window->getSize().x;
    const float screenHeight = this->window->getSize().y;
    const float yDistance = 150.f;

    std::vector<std::string> items = { "Start Game", "Exit" };
    const float totalMenuHeight = items.size() * yDistance;
    const float startY = (screenHeight - totalMenuHeight) / 2.f + 100.f;

    this->title.setFont(this->font);
    this->title.setString("Tower Defense");
    this->title.setCharacterSize(250);
    this->title.setFillColor(sf::Color(254, 153, 1));
    this->title.setOutlineColor(sf::Color(104, 13, 14));
    this->title.setOutlineThickness(7);
    this->title.setStyle(sf::Text::Bold);
    this->title.setPosition((screenWidth - this->title.getLocalBounds().width) / 2.f, 20.f);

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(this->font);
        text.setString(items[i]);
        text.setCharacterSize(150);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(5);

        sf::FloatRect textBounds = text.getLocalBounds();
        float textWidth = textBounds.width;
        float textHeight = textBounds.height;

        text.setPosition((screenWidth - textWidth) / 2.f, startY + i * yDistance);
        text.setOrigin(textBounds.left, textBounds.top + textHeight / 2);
        text.setFillColor(sf::Color::White);

        this->menuItems.push_back(text);
    }
}

Menu::~Menu() {}

//-----------------------------------
//             Accessors
//-----------------------------------

int Menu::getSelectedItemIndex() const { return this->selectedItemIndex; }

//-----------------------------------
//          Public methods
//-----------------------------------

int Menu::startMenu() {
    bool isRunning = true;

    while (isRunning && this->window->isOpen()) {
        handleInput(isRunning);
        render();
    }
    return this->selectedItemIndex;
}

void Menu::render() {
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    this->window->draw(this->title);
    for (const auto& item : this->menuItems) {
        this->window->draw(item);
    }
    this->window->display();
}

void Menu::handleInput(bool& isRunning) {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

            for (size_t i = 0; i < this->menuItems.size(); ++i) {
                if (this->menuItems[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    this->menuItems[this->selectedItemIndex].setFillColor(sf::Color::White);
                    this->selectedItemIndex = i;
                    this->menuItems[this->selectedItemIndex].setFillColor(i == 1 ? sf::Color::Red : sf::Color::Green);
                    break;
                }
                else {
                    this->menuItems[this->selectedItemIndex].setFillColor(sf::Color::White);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
                if (this->menuItems[this->selectedItemIndex].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (this->selectedItemIndex == 0) {
                        isRunning = false;
                    }
                    else if (this->selectedItemIndex == 1) {
                        this->window->close();
                    }
                }
            }
        }
    }
}
