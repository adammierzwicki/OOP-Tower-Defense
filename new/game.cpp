#include "game.h"
#include <fstream>
#include <algorithm>

//-----------------------------------
//          Helper functions
//-----------------------------------

void Game::initVariables()
{
    this->level = 1;
    this->window = new WindowHandler();
    this->endGame = false;
    this->playerHp = 100;
    this->money = 100;

    this->selectBox.setPointCount(4);
    this->selectBox.setPoint(0, sf::Vector2f(0.0f, 33.0f));
    this->selectBox.setPoint(1, sf::Vector2f(66.0f, 0.0f));
    this->selectBox.setPoint(2, sf::Vector2f(132.0f, 33.0f));
    this->selectBox.setPoint(3, sf::Vector2f(66.0f, 66.0f));
    this->selectBox.setOrigin(66.0f, 0.0f);

    this->selectBox.setFillColor(sf::Color::Transparent);
    this->selectBox.setOutlineColor(sf::Color::Red);
    this->selectBox.setOutlineThickness(5.0f);
}

void Game::loadLevel(int level)
{
    std::string path = "levels/level_" + std::to_string(level) + ".map";
    std::cout << path << std::endl;
    std::fstream file(path);
    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);
        while (!line.empty())
        {
            float x = std::stof(line.substr(0, line.find(',')));
            float y = std::stof(line.substr(line.find(',') + 1));
            std::cout << x << " " << y << std::endl;
            this->enemyPath.push_back(sf::Vector2f(x, y));
            std::getline(file, line);
        }
        while (std::getline(file, line))
        {
            std::string enemyType = line.substr(0, line.find(','));
            int num = std::stoi(line.substr(line.find(',') + 1));
            for (int i = 0; i < num; i++)
            {
                this->addEnemy(enemyType[0]);
            }
        }
    }
    else
    {
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

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Game::Game()
{
    this->initVariables();

    // Adam: I commented it here because I moved it to startGame function
    // because when running menu, then enemies were created

    // this->loadLevel(1);
    // this->initWorld();
}

Game::~Game()
{
    delete this->window;
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        delete this->enemies[i];
    }
    for (size_t i = 0; i < this->towers.size(); i++)
    {
        delete this->towers[i];
    }
}

//-----------------------------------
//          Game functions
//-----------------------------------

void Game::update()
{
    this->window->update();
}

void Game::render()
{
    std::vector<sf::Drawable *> screenContent;
    if (cursorOnMap)
    {
        screenContent.push_back(&selectBox);
    }
    screenContent.insert(screenContent.end(), this->enemies.begin(), this->enemies.end());
    screenContent.insert(screenContent.end(), this->towers.begin(), this->towers.end());

    this->window->render(this->background, screenContent);
}

void Game::startGame() {
    this->startingScreen();
    if (!this->window->running()) {
        return;
    }

    this->loadLevel(1);
    this->initWorld();

    this->gameLoop();
}

bool Game::isCursorOnMap()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    sf::Vector2f p1(142, 507);
    sf::Vector2f p2(891, 132);
    sf::Vector2f p3(1763, 568);
    sf::Vector2f p4(1014, 943);

    auto sign = [](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    };

    bool b1, b2, b3, b4;

    b1 = sign(mousePosF, p1, p2) < 0.0f;
    b2 = sign(mousePosF, p2, p3) < 0.0f;
    b3 = sign(mousePosF, p3, p4) < 0.0f;
    b4 = sign(mousePosF, p4, p1) < 0.0f;

    if ((b1 == b2) && (b2 == b3) && (b3 == b4))
    {
        return true;
    }
    return false;
}

sf::Vector2f Game::getCursorProjection()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f mapOrigin = sf::Vector2f(142.0f, 508.0f);
    sf::Vector2f tileSize = sf::Vector2f(132.0f, 66.0f);
    sf::Vector2f tileHalfSize = tileSize / 2.0f;
    // Convert screen coordinates to map coordinates
    sf::Vector2f mapPos = mousePosF - mapOrigin;

    // Calculate the tile coordinates
    int tileX = static_cast<int>(std::floor((mapPos.x / tileHalfSize.x + mapPos.y / tileHalfSize.y) / 2));
    int tileY = static_cast<int>(std::floor((mapPos.y / tileHalfSize.y - mapPos.x / tileHalfSize.x) / 2));

    // Calculate the top-left corner of the tile
    sf::Vector2f vec = sf::Vector2f(tileX - tileY, tileX + tileY);
    sf::Vector2f tilePos;
    tilePos.x = mapOrigin.x + vec.x * tileHalfSize.x;
    tilePos.y = mapOrigin.y + vec.y * tileHalfSize.y;

    return tilePos;
}

void Game::updateSelectBox()
{

    if (isCursorOnMap())
    {
        this->selectBox.setPosition(getCursorProjection());
        this->cursorOnMap = true;
    }
    else
    {
        this->cursorOnMap = false;
    }
}

void Game::placeTower()
{
    if (isCursorOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Gun *gun = new MachineGun();
        sf::Vector2f pos = getCursorProjection();
        pos -= sf::Vector2f(0.0f, -15.0f);
        Tower *tower = new Tower(pos, 1, 100, gun);
        std::cout << "Tower placed at " << tower->getPosition().x << " " << tower->getPosition().y << std::endl;
        this->towers.push_back(tower);
        sort(this->towers.begin(), this->towers.end(), [](Tower *a, Tower *b)
             { return a->getPosition().y < b->getPosition().y; });
    }
}

void Game::gameLoop()
{
    while (this->window->running())
    {

        this->updateSelectBox();
        this->placeTower();
        this->update();
        this->render();
    }
}

void Game::startingScreen()
{
    Menu menu(this->window->getWindow());
    int choice = menu.startMenu();

    if (choice == 0) { //this ensures that if "play" is selected, the game will start
        return;
    }
}