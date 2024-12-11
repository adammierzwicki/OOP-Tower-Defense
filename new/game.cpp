#include "game.h"
#include <fstream>

void Game::initVariables()
{
    this->level = 1;
    this->window = new WindowHandler();
    this->endGame = false;
    this->playerHp = 100;
    this->money = 100;
}

void Game::loadLevel(int level) {
    std::string path = "levels/level_" + std::to_string(level) + ".map";
    std::cout << path <<std::endl;
    std::fstream file(path);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        while (!line.empty()) {
            float x = std::stof(line.substr(0, line.find(',')));
            float y = std::stof(line.substr(line.find(',') + 1));
            std::cout << x << " " << y << std::endl;
            this->enemyPath.push_back(sf::Vector2f(x, y));
            std::getline(file, line);
        }
        while (std::getline(file, line)) {
            std::string enemyType = line.substr(0, line.find(','));
            int num = std::stoi(line.substr(line.find(',') + 1));
            for (int i = 0; i < num; i++) {
                this->addEnemy(enemyType[0]);
            }
        }
    }
    else {
        std::cout << "Error: could not load level" << std::endl;
    }
    file.close();

}

void Game::addEnemy(char enemyType)
{
    Enemy *enemy;
    switch (enemyType)
    {
    case 'P':
        enemy = new Peasant();
        break;
    case 'W':
        enemy = new Warrior();
        break;
    case 'H':
        enemy = new HeavyKnight();
        break;
    default:
        enemy = new Peasant();
        break;
    }
    this->enemies.push_back(enemy);
}

void Game::initWorld()
{
    std::string path = "textures/level_" + std::to_string(this->level) + ".png";
    if (!this->backgroundTexture.loadFromFile(path))
    {
        std::cout << "Error: could not load level image" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture, true);
}

// constructor and destructor
Game::Game()
{
    this->initVariables();
    this->loadLevel(1);
    this->initWorld();
}
Game::~Game()
{
    delete this->window;
    //todo: enemy destructors?
    // for (size_t i = 0; i < this->enemies.size(); i++)
    // {
    //     delete this->enemies[i];
    // }
}

// functions
void Game::update()
{

}
void Game::render()
{

}
void Game::startGame()
{
    while (this->window->running())
    {   
        this->window->update();
        this->window->render(this->background, this->enemies);
    }
}