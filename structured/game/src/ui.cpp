#include "../inc/ui.h"
#include <iostream>

UI::UI(sf::RenderWindow* window) : window(window), selectedButtonIndex(0) {
    if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    roundDisplay.setFont(font);
    roundDisplay.setCharacterSize(50);
    roundDisplay.setFillColor(sf::Color::White);
    // roundDisplay.setString("Round:");
    roundDisplay.setPosition(20, 20);

    healthDisplay.setFont(font);
    healthDisplay.setCharacterSize(50);
    healthDisplay.setFillColor(sf::Color::White);
    // healthDisplay.setString("Health:");
    healthDisplay.setPosition(20, 80);

    moneyDisplay.setFont(font);
    moneyDisplay.setCharacterSize(50);
    moneyDisplay.setFillColor(sf::Color::White);
    // moneyDisplay.setString("Money:");
    moneyDisplay.setPosition(20, 140);
    

    const float buttonWidth = 300.0f;
    const float buttonHeight = 80.0f;
    const float buttonSpacing = 10.0f;
    const float xPosition = 50.0f;
    const float yPosition = window->getSize().y - buttonHeight - 50.0f;

    gunType1Button.setFont(font);
    gunType1Button.setCharacterSize(40);
    gunType1Button.setFillColor(sf::Color::White);
    gunType1Button.setString("Gun Type 1");
    sf::FloatRect textBounds = gunType1Button.getLocalBounds();
    float textWidth = textBounds.width;
    float textHeight = textBounds.height;
    gunType1Button.setOrigin(textBounds.left, textBounds.top + textHeight / 2);
    gunType1Button.setPosition(xPosition, yPosition);


    gunType2Button.setFont(font);
    gunType2Button.setCharacterSize(40);
    gunType2Button.setFillColor(sf::Color::White);
    gunType2Button.setString("Gun Type 2");
    sf::FloatRect textBounds2 = gunType2Button.getLocalBounds();
    float textWidth2 = textBounds2.width;
    float textHeight2 = textBounds2.height;
    gunType2Button.setOrigin(textBounds2.left, textBounds2.top + textHeight2 / 2);
    gunType2Button.setPosition(xPosition + buttonWidth + buttonSpacing, yPosition);


    gunType3Button.setFont(font);
    gunType3Button.setCharacterSize(40);
    gunType3Button.setFillColor(sf::Color::White);
    gunType3Button.setString("Gun Type 3");
    sf::FloatRect textBounds3 = gunType3Button.getLocalBounds();
    float textWidth3 = textBounds3.width;
    float textHeight3 = textBounds3.height;
    gunType3Button.setOrigin(textBounds3.left, textBounds3.top + textHeight3 / 2);
    gunType3Button.setPosition(xPosition + 2 * (buttonWidth + buttonSpacing), yPosition);


    startGameButton.setFont(font);
    startGameButton.setCharacterSize(40);
    startGameButton.setFillColor(sf::Color::White);
    startGameButton.setString("Start Game");
    sf::FloatRect textBounds4 = startGameButton.getLocalBounds();
    float textWidth4 = textBounds4.width;
    float textHeight4 = textBounds4.height;
    startGameButton.setOrigin(textBounds4.left, textBounds4.top + textHeight4 / 2);
    startGameButton.setPosition(window->getSize().x - (xPosition + buttonWidth + buttonSpacing), yPosition);

}
// UI::UI(sf::RenderWindow* window) : window(window), selectedButtonIndex(-1) {
//     if (!font.loadFromFile("fonts/BoldKei-nRAWP.ttf")) {
//         throw std::runtime_error("Failed to load font");
//     }

//     // Initialize texts for round, health, and money displays
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

//     const float buttonWidth = 300.0f;
//     const float buttonHeight = 80.0f;
//     const float buttonSpacing = 10.0f;
//     const float xPosition = 50.0f;
//     const float yPosition = window->getSize().y - buttonHeight - 50.0f;

//     std::vector<std::string> buttonLabels = {"Gun Type 1", "Gun Type 2", "Gun Type 3", "Start Game"};

//     // Create all buttons and store them in the vector
//     for (size_t i = 0; i < buttonLabels.size(); ++i) {
//         sf::Text button;
//         button.setFont(font);
//         button.setCharacterSize(40);
//         button.setString(buttonLabels[i]);
//         button.setFillColor(sf::Color::White);

//         sf::FloatRect textBounds = button.getLocalBounds();
//         button.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
//         button.setPosition(xPosition + i * (buttonWidth + buttonSpacing), yPosition);

//         if (i == 0) {
//             button.setFillColor(sf::Color::Green);  // Highlight first button initially
//         }

//         buttons.push_back(button);
//     }
// }


UI::~UI() {}

void UI::startUI() {

    this->handleInput();
    // this->render();
    // handleInput(isRunning);
    // render();
    
}

void UI::render() {
    // window->draw(backgroundSprite);

    window->draw(roundDisplay);
    window->draw(healthDisplay);
    window->draw(moneyDisplay);

    // for (const auto& button : buttons) {
    //     window->draw(button);
    // }
    window->draw(gunType1Button);
    window->draw(gunType2Button);
    window->draw(gunType3Button);
    window->draw(startGameButton);
    // window->display();
}

void UI::handleInput() {
    sf::Event event;
    // std::cout << "Handling input\n";
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            if (gunType1Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedButtonIndex = 1;
                std::cout << "Gun Type 1 selected\n";
            } else if (gunType2Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedButtonIndex = 2;
                std::cout << "Gun Type 2 selected\n";
            } else if (gunType3Button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                selectedButtonIndex = 3;
                std::cout << "Gun Type 3 selected\n";
            } else if (startGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Game Started\n";
            }
        }
    }
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