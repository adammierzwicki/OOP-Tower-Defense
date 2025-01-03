#include "../inc/windowHandler.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

WindowHandler::WindowHandler() {
    this->initWindow();
}

WindowHandler::~WindowHandler() {
    delete this->window;
}

//-----------------------------------
//          Private methods
//-----------------------------------

void WindowHandler::initWindow() {
    this->videoMode = sf::VideoMode(1920, 1080);
    this->window = new sf::RenderWindow(this->videoMode, "Tower Defense", sf::Style::Close | sf::Style::Titlebar);
    this->window->setPosition(sf::Vector2i(0, 0));
    this->window->setFramerateLimit(60);
}

void WindowHandler::pollEvents() {
    this->events.clear();
    while (this->window->pollEvent(this->windowEvent)) {
        events.push_back(this->windowEvent);
        switch (this->windowEvent.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->windowEvent.key.code == sf::Keyboard::Q && this->windowEvent.key.control) {
                this->window->close();
            }
            break;
        default:
            break;
        }
    }
}

//-----------------------------------
//             Accessors
//-----------------------------------

sf::RenderWindow* WindowHandler::getWindow() const { return this->window; }

const std::vector<sf::Event>& WindowHandler::getEvents() const { return this->events; }

//-----------------------------------
//          Public methods
//-----------------------------------

bool WindowHandler::mouseLeftClicked() {
    if (this->windowEvent.type == this->windowEvent.MouseButtonReleased && this->windowEvent.mouseButton.button == sf::Mouse::Left) {
        return true;
    }
    return false;
}

void WindowHandler::render(sf::Sprite background, std::vector<DrawableObject*> screenContent, UI* ui) {
    this->window->clear();
    this->window->draw(background);
    for (const DrawableObject* object : screenContent) {
        this->window->draw(*object);
    }
    ui->render();
    this->window->display();
}

bool WindowHandler::running() const { return this->window->isOpen(); }

void WindowHandler::update() { this->pollEvents(); }