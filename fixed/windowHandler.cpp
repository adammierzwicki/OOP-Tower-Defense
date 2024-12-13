#include "windowHandler.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

// constructor and destructor
WindowHandler::WindowHandler()
{
    this->initWindow();
}

WindowHandler::~WindowHandler()
{
    delete this->window;
}

//-----------------------------------
//          Private methods
//-----------------------------------

void WindowHandler::initWindow()
{
    this->videoMode = sf::VideoMode(1920, 1080);
    this->window = new sf::RenderWindow(this->videoMode, "Tower Defense", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
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
        if( this->windowEvent.type == this->windowEvent.MouseButtonReleased && this->windowEvent.mouseButton.button == sf::Mouse::Right ) {
            std::cout << "RiGHT" << std::endl;
        }
    }
}



//-----------------------------------
//             Accessors
//-----------------------------------

sf::RenderWindow *WindowHandler::getWindow() { return this->window; }

//-----------------------------------
//          Public methods
//-----------------------------------

bool WindowHandler::mouseLeftClicked()
{
    if (this->windowEvent.type == this->windowEvent.MouseButtonReleased && this->windowEvent.mouseButton.button == sf::Mouse::Left)
    {
        return true;
    }
    return false;
}

void WindowHandler::render(sf::Sprite background, std::vector<sf::Drawable *> screenContent)
{

    this->window->clear();

    this->window->draw(background);

    // render all objects
    for (size_t i = 0; i < screenContent.size(); i++)
    {
        // screenContent[i]->draw(*this->window, sf::RenderStates::Default);
        this->window->draw(*screenContent[i]);
    }

    this->window->display();
}

const bool WindowHandler::running() const { return this->window->isOpen(); }

void WindowHandler::update() { this->pollEvents(); }
