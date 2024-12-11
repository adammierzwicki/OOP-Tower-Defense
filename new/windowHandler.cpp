#include "WindowHandler.h"

void WindowHandler::initVariables()
{

}

void WindowHandler::initWindow()
{
    this->videoMode = sf::VideoMode(1920, 1080);
    this->window = new sf::RenderWindow(this->videoMode, "Tower Defense", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

// constructor and destructor
WindowHandler::WindowHandler()
{
    this->initVariables();
    this->initWindow();
}

WindowHandler::~WindowHandler()
{
    delete this->window;
}

// functions
const bool WindowHandler::running() const
{
    return this->window->isOpen();
}

void WindowHandler::pollEvents()
{
    while (this->window->pollEvent(this->windowEvent))
    {
        switch (this->windowEvent.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->windowEvent.key.code == sf::Keyboard::Q && this->windowEvent.key.control)
                {
                    this->window->close();
                }
                break;
        }
    }
}

void WindowHandler::update()
{
    this->pollEvents();
}

void WindowHandler::render(sf::Sprite background, std::vector<Enemy *> enemies)
{
    this->window->clear();
    
    this->window->draw(background);
    // render all objects
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(this->window);
    }

    this->window->display();
}