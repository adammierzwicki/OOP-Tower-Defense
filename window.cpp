#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Tower Defense Game", sf::Style::Close);

    sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(25.0f, 25.0f);

    sf::RectangleShape tower(sf::Vector2f(100.0f, 100.0f));
    sf::Texture towerTexture;
    if (!towerTexture.loadFromFile("textures/torreComum.png")) {
        std::cerr << "Error: Cannot load tower texture!" << std::endl;
    }
    tower.setTexture(&towerTexture);
    tower.setPosition(200.0f, 200.0f);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("textures/grass_template2.jpg");
    std::cout << backgroundTexture.getSize().x << " " << backgroundTexture.getSize().y << std::endl;
    sf::Sprite background(backgroundTexture);

    // backgroundTexture.setRepeated(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                printf("New window size (%i, %i)\n", event.size.width, event.size.height);
                break;
            // case sf::Event::TextEntered:
            //     if (event.text.unicode < 128) 
            //     {
            //         printf("%c", event.text.unicode);
            //     }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, (float)mousePos.y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.0f, 0.1f);
        }

        window.clear();
        window.draw(background);
        window.draw(player);
        window.draw(tower);
        window.display();
    }

    return 0;
}