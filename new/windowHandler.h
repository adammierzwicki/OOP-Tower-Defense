#include <iostream>
#include <SFML/Graphics.hpp>
#include "enemy.h"

class WindowHandler
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event windowEvent;

    void initWindow();
    void initVariables();

public:
    // constructor and destructor
    WindowHandler();
    ~WindowHandler();

    // functions
    const bool running() const;
    void pollEvents();

    void update();
    void render(sf::Sprite background, std::vector<Enemy *> enemies);
};