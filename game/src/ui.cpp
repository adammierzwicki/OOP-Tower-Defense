#include "../inc/ui.h"

// UI::UI(WindowHandler* windowHandler) : windowHandler(windowHandler), selectedButtonIndex(-1) {
//     if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
//         throw std::runtime_error("Failed to load font");
//     }

//     roundDisplay.setFont(font);
//     roundDisplay.setCharacterSize(50);
//     roundDisplay.setFillColor(sf::Color::White);
//     roundDisplay.setPosition(20, 20);

//     healthDisplay.setFont(font);
//     healthDisplay.setCharacterSize(50);
//     healthDisplay.setFillColor(sf::Color::White);
//     healthDisplay.setPosition(20, 80);

//     moneyDisplay.setFont(font);
//     moneyDisplay.setCharacterSize(50);
//     moneyDisplay.setFillColor(sf::Color::White);
//     moneyDisplay.setPosition(20, 140);

//     const float buttonWidth = 500.0f;
//     const float buttonHeight = 80.0f;
//     const float buttonSpacing = 50.0f;
//     float xPosition = 50.0f;
//     const float yPosition = windowHandler->getWindow()->getSize().y - buttonHeight - 50.0f;

//     std::vector<std::string> buttonLabels = {"Machine Gun Tower", "High Damage Gun Tower", "Sniper Rifle Tower", "Start Game"};

//     for (size_t i = 0; i < buttonLabels.size(); ++i) {
//         sf::Text button;
//         button.setFont(font);
//         button.setString(buttonLabels[i]);
//         button.setCharacterSize(40);
//         button.setFillColor(sf::Color::White);

//         sf::FloatRect textBounds = button.getLocalBounds();
//         float textWidth = textBounds.width;
//         float textHeight = textBounds.height;
//         std::cout << "textWidth: " << textWidth << std::endl;
//         std::cout << xPosition + i * (textWidth + buttonSpacing) << std::endl;
//         button.setPosition(xPosition , yPosition);
//         button.setOrigin(textBounds.left, textBounds.top + textHeight / 2);
//         xPosition += textWidth + buttonSpacing;
//         std::cout << "Button " << i << std::endl;
//         std::cout << button.getPosition().x << " " << button.getPosition().y << std::endl;
//         std::cout << button.getOrigin().x << " " << button.getOrigin().y << std::endl;
//         std::cout << button.getGlobalBounds().width<< " " << button.getGlobalBounds().height << std::endl;
//         buttons.push_back(button);
//     }
// }
UI::UI(WindowHandler* windowHandler) : windowHandler(windowHandler), selectedButtonIndex(-1) {
    if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    roundDisplay.setFont(font);
    roundDisplay.setCharacterSize(50);
    roundDisplay.setFillColor(sf::Color::White);
    roundDisplay.setPosition(20, 20);

    healthDisplay.setFont(font);
    healthDisplay.setCharacterSize(50);
    healthDisplay.setFillColor(sf::Color::White);
    healthDisplay.setPosition(20, 80);

    moneyDisplay.setFont(font);
    moneyDisplay.setCharacterSize(50);
    moneyDisplay.setFillColor(sf::Color::White);
    moneyDisplay.setPosition(20, 140);

    const float buttonWidth = 400.0f;
    const float buttonHeight = 100.0f;
    const float buttonSpacing = 50.0f;
    float xPosition = 50.0f;
    float yPosition = windowHandler->getWindow()->getSize().y - buttonHeight - 200.0f;

    std::vector<std::pair<std::string, int>> buttonData = {
        {"Machine Gun Tower", 100},
        {"High Damage Tower", 200},
        {"Sniper Tower", 300},
        {"Start Game", 0},
        {"Upgrade", 70}
    };

    for (const auto& [label, price] : buttonData) {
        Button button;
        if (label != "Start Game") {
            button.rectangle.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.rectangle.setFillColor(sf::Color::Black);
            button.rectangle.setOutlineColor(sf::Color::White);
            button.rectangle.setOutlineThickness(2.0f);
            button.rectangle.setPosition(xPosition, yPosition);

            button.nameText.setFont(font);
            button.nameText.setString(label);
            button.nameText.setCharacterSize(30);
            button.nameText.setFillColor(sf::Color::White);
            // sf::FloatRect nameBounds = button.nameText.getLocalBounds();
            button.nameText.setPosition(
                xPosition + 20.0f,
                yPosition + 10.0f
            );

            button.priceText.setFont(font);
            button.priceText.setString("Price: " + std::to_string(price));
            button.priceText.setCharacterSize(25);
            button.priceText.setFillColor(sf::Color::White);
            // sf::FloatRect priceBounds = button.priceText.getLocalBounds();
            button.priceText.setPosition(
                xPosition + 20.0f,
                yPosition + buttonHeight - 40.0f
            );
        } else {
            button.rectangle.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.rectangle.setFillColor(sf::Color::Black);
            button.rectangle.setOutlineColor(sf::Color::White);
            button.rectangle.setOutlineThickness(2.0f);
            button.rectangle.setPosition(xPosition, yPosition);

            button.nameText.setFont(font);
            button.nameText.setString(label);
            button.nameText.setCharacterSize(55);
            button.nameText.setFillColor(sf::Color::White);
            // sf::FloatRect nameBounds = button.nameText.getLocalBounds();
            button.nameText.setPosition(
                xPosition + 20.0f,
                yPosition + 10.0f
            );

            // button.priceText.setFont(font);
            // button.priceText.setString("Price: $" + std::to_string(price));
            // button.priceText.setCharacterSize(25);
            // button.priceText.setFillColor(sf::Color::Yellow);
            // sf::FloatRect priceBounds = button.priceText.getLocalBounds();
            // button.priceText.setPosition(
            //     xPosition + 20.0f,
            //     yPosition + buttonHeight - 40.0f
            // );
        }

        if (label == "Machine Gun Tower"){
            yPosition += buttonHeight + buttonSpacing;
        }
        else if (label == "High Damage Tower"){
            xPosition += buttonWidth + buttonSpacing;
        }
        else if (label == "Sniper Tower")
        {
            yPosition = windowHandler->getWindow()->getSize().y - buttonHeight - 200.0f;
            xPosition = windowHandler->getWindow()->getSize().x - buttonWidth - 50.0f;
        }
        else if (label == "Start Game")
        {
            xPosition = windowHandler->getWindow()->getSize().x - buttonWidth - 50.0f;
            yPosition += buttonHeight + buttonSpacing;
        }
        buttons.push_back(button);
    }
}


UI::~UI() {}


void UI::startUI() {

    this->handleInput();
    // this->render();
    // handleInput(isRunning);
    // render();
    
}

// void UI::render() {
//     windowHandler->getWindow()->draw(roundDisplay);
//     windowHandler->getWindow()->draw(healthDisplay);
//     windowHandler->getWindow()->draw(moneyDisplay);

//     for (const auto& button : buttons) {
//         windowHandler->getWindow()->draw(button);
//     }
// }
void UI::render() {
    windowHandler->getWindow()->draw(roundDisplay);
    windowHandler->getWindow()->draw(healthDisplay);
    windowHandler->getWindow()->draw(moneyDisplay);

    for (const auto& button : buttons) {
        windowHandler->getWindow()->draw(button.rectangle);
        windowHandler->getWindow()->draw(button.nameText);
        windowHandler->getWindow()->draw(button.priceText);
    }
}


// ButtonType UI::handleInput()
// {
//     std::vector<sf::Event> events = this->windowHandler->getEvents();
//     for (const auto &event : events)
//     {
//         if (event.type == sf::Event::Closed)
//         {
//             windowHandler->getWindow()->close();
//         }
//         else if (event.type == sf::Event::MouseMoved) {
//             sf::Vector2i mousePos = sf::Mouse::getPosition(*windowHandler->getWindow());

//             for (size_t i = 0; i < buttons.size(); ++i) {
//                 if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//                     buttons[i].setFillColor(sf::Color::Green);
//                 } else {
//                     buttons[i].setFillColor(sf::Color::White);
//                 }
//             }
//         }
//         else if (event.type == sf::Event::MouseButtonPressed)
//         {
//             if (event.mouseButton.button == sf::Mouse::Left)
//             {
//                 sf::Vector2i mousePos = sf::Mouse::getPosition(*windowHandler->getWindow());

//                 // Check if a button is clicked
//                 for (size_t i = 0; i < buttons.size(); ++i)
//                 {
//                     if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
//                     {
//                         selectedButtonIndex = static_cast<int>(i);
//                         switch(i){
//                             case 0:
//                                 std::cout << "Gun Type 1 selected\n";
//                                 return ButtonType::GUN_TYPE_1;
//                             case 1:
//                                 std::cout << "Gun Type 2 selected\n";
//                                 return ButtonType::GUN_TYPE_2;
//                             case 2:
//                                 std::cout << "Gun Type 3 selected\n";
//                                 return ButtonType::GUN_TYPE_3;
//                             case 3:
//                                 std::cout << "Game Started\n";
//                                 return ButtonType::START_GAME;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return ButtonType::NONE;
// }
ButtonType UI::handleInput()
{
    std::vector<sf::Event> events = this->windowHandler->getEvents();
    for (const auto& event : events) {
        if (event.type == sf::Event::Closed) {
            windowHandler->getWindow()->close();
        } else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*windowHandler->getWindow());

            for (auto& button : buttons) {
                if (button.rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    button.rectangle.setFillColor(sf::Color::Green);
                } else {
                    button.rectangle.setFillColor(sf::Color::Black);
                }
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*windowHandler->getWindow());

                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].rectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectedButtonIndex = static_cast<int>(i);
                        switch (i) {
                            case 0:
                                std::cout << "Gun Type 1 selected\n";
                                return ButtonType::MACHINE_GUN;
                            case 1:
                                std::cout << "Gun Type 2 selected\n";
                                return ButtonType::HIGH_DAMAGE_GUN;
                            case 2:
                                std::cout << "Gun Type 3 selected\n";
                                return ButtonType::SNIPER_RIFLE;
                            case 3:
                                std::cout << "Game Started\n";
                                return ButtonType::START_GAME;
                            case 4:
                                std::cout << "Upgrade\n";
                                return ButtonType::UPGRADE;
                        }
                    }
                }
            }
        }
    }
    return ButtonType::NONE;
}



void UI::setRoundText(int round) {
    roundDisplay.setString("Round: " + std::to_string(round));
}

void UI::setHealthText(int health) {
    healthDisplay.setString("Health: " + std::to_string(health));
}

void UI::setMoneyText(int money) {
    moneyDisplay.setString("Money: " + std::to_string(money));
}

int UI::getSelectedButton() const {
    return selectedButtonIndex;
}