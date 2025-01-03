#include "../inc/ui.h"

#include "../inc/prices.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

UI::UI(WindowHandler* windowHandler) : windowHandler(windowHandler), selectedButtonIndex(-1) {
    this->logger = Logger::getInstance();

    if (!this->font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load font (\"./fonts/BoldKei-nRAWP.ttf\")", "UI::UI()", __LINE__);
        throw std::runtime_error("Failed to load font");
    }

    this->roundDisplay.setFont(this->font);
    this->roundDisplay.setCharacterSize(80);
    this->roundDisplay.setFillColor(sf::Color::White);
    this->roundDisplay.setPosition(20, 20);

    this->healthDisplay.setFont(this->font);
    this->healthDisplay.setCharacterSize(80);
    this->healthDisplay.setFillColor(sf::Color::White);
    this->healthDisplay.setPosition(20, 80);

    this->moneyDisplay.setFont(this->font);
    this->moneyDisplay.setCharacterSize(80);
    this->moneyDisplay.setFillColor(sf::Color::White);
    this->moneyDisplay.setPosition(20, 140);

    const float buttonWidth = 400.f;
    const float buttonHeight = 100.f;
    const float buttonSpacing = 50.f;
    float xPosition = 50.f;
    float yPosition = windowHandler->getWindow()->getSize().y - buttonHeight - 200.f;

    std::vector<std::pair<std::string, int>> buttonData = {
        {"Machine Gun Tower", Prices::machineGunTower},
        {"High Damage Tower", Prices::highDamageTower},
        {"Sniper Tower", Prices::sniperTower},
        {"Start Game", 0},
        {"Upgrade", Prices::upgrade}
    };

    for (const auto& [label, price] : buttonData) {
        Button button;
        if (label != "Start Game") {
            button.rectangle.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.rectangle.setFillColor(sf::Color::Black);
            button.rectangle.setOutlineColor(sf::Color::White);
            button.rectangle.setOutlineThickness(2.f);
            button.rectangle.setPosition(xPosition, yPosition);

            button.nameText.setFont(this->font);
            button.nameText.setString(label);
            button.nameText.setCharacterSize(30);
            button.nameText.setFillColor(sf::Color::White);
            button.nameText.setPosition(xPosition + 20.f,
                yPosition + 10.f
            );

            button.priceText.setFont(this->font);
            button.priceText.setString("Price: " + std::to_string(price));
            button.priceText.setCharacterSize(25);
            button.priceText.setFillColor(sf::Color::White);
            button.priceText.setPosition(xPosition + 20.f, yPosition + buttonHeight - 40.f);
        }
        else {
            button.rectangle.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.rectangle.setFillColor(sf::Color::Black);
            button.rectangle.setOutlineColor(sf::Color::White);
            button.rectangle.setOutlineThickness(2.f);
            button.rectangle.setPosition(xPosition, yPosition);

            button.nameText.setFont(this->font);
            button.nameText.setString(label);
            button.nameText.setCharacterSize(55);
            button.nameText.setFillColor(sf::Color::White);
            button.nameText.setPosition(xPosition + 20.f, yPosition + 10.f);
        }

        if (label == "Machine Gun Tower") {
            yPosition += buttonHeight + buttonSpacing;
        }
        else if (label == "High Damage Tower") {
            xPosition += buttonWidth + buttonSpacing;
        }
        else if (label == "Sniper Tower") {
            yPosition = windowHandler->getWindow()->getSize().y - buttonHeight - 200.f;
            xPosition = windowHandler->getWindow()->getSize().x - buttonWidth - 50.f;
        }
        else if (label == "Start Game") {
            xPosition = windowHandler->getWindow()->getSize().x - buttonWidth - 50.f;
            yPosition += buttonHeight + buttonSpacing;
        }
        this->buttons.push_back(button);
    }
}

UI::~UI() {}

//-----------------------------------
//             Accessors
//-----------------------------------

int UI::getSelectedButton() const { return this->selectedButtonIndex; }

//-----------------------------------
//             Modifiers
//-----------------------------------

void UI::setRoundText(int round) {
    this->roundDisplay.setString("Round: " + std::to_string(round));
}

void UI::setHealthText(int health) {
    this->healthDisplay.setString("Health: " + std::to_string(health));
}

void UI::setMoneyText(int money) {
    this->moneyDisplay.setString("Money: " + std::to_string(money));
}

//-----------------------------------
//          Public methods
//-----------------------------------

void UI::render() {
    windowHandler->getWindow()->draw(this->roundDisplay);
    windowHandler->getWindow()->draw(this->healthDisplay);
    windowHandler->getWindow()->draw(this->moneyDisplay);

    for (const auto& button : this->buttons) {
        windowHandler->getWindow()->draw(button.rectangle);
        windowHandler->getWindow()->draw(button.nameText);
        windowHandler->getWindow()->draw(button.priceText);
    }
}

ButtonType UI::handleInput() {
    std::vector<sf::Event> events = this->windowHandler->getEvents();
    for (const auto& event : events) {
        if (event.type == sf::Event::Closed) {
            this->windowHandler->getWindow()->close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->windowHandler->getWindow());

            for (auto& button : this->buttons) {
                if (button.rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    button.rectangle.setFillColor(sf::Color::Green);
                }
                else {
                    button.rectangle.setFillColor(sf::Color::Black);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*this->windowHandler->getWindow());

                for (size_t i = 0; i < this->buttons.size(); ++i) {
                    if (this->buttons[i].rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->selectedButtonIndex = static_cast<int>(i);
                        switch (i) {
                        case 0:
                            this->logger->log(LogLevel::INFO, "Machine Gun Tower selected");
                            return ButtonType::MACHINE_GUN;
                        case 1:
                            this->logger->log(LogLevel::INFO, "High Damage Tower selected");
                            return ButtonType::HIGH_DAMAGE_GUN;
                        case 2:
                            this->logger->log(LogLevel::INFO, "Sniper Tower selected");
                            return ButtonType::SNIPER_RIFLE;
                        case 3:
                            this->logger->log(LogLevel::INFO, "Game Started");
                            return ButtonType::START_GAME;
                        case 4:
                            this->logger->log(LogLevel::INFO, "Upgrade selected");
                            return ButtonType::UPGRADE;
                        }
                    }
                }
            }
        }
    }
    return ButtonType::NONE;
}