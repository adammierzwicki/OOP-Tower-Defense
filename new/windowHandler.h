#include <iostream>
#include <SFML/Graphics.hpp>

class WindowHandler
{
private:
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event windowEvent;

    // functions
    void initWindow();
    void initVariables();

public:
    // constructor and destructor
    WindowHandler();
    ~WindowHandler();

    // getter
    sf::RenderWindow *getWindow();

    // functions
    const bool running() const;
    void pollEvents();
    void update();
    void render(sf::Sprite background, std::vector<sf::Drawable *> screenContent);
};