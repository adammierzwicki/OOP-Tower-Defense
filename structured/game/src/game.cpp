#include <algorithm>
#include <fstream>

#include "../inc/drawableObject.h"
#include "../inc/game.h"
#include "../inc/ui.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Game::Game()
{
    this->initVariables();
}

Game::~Game()
{
    delete this->window;
    // delete this->selectBox;
    delete this->ui;
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        delete this->enemies[i];
    }
    for (size_t i = 0; i < this->towers.size(); i++)
    {
        delete this->towers[i];
    }
    delete this->levelInfo;
    delete this->selectBox;
}

//-----------------------------------
//          Private methods
//-----------------------------------

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
    }
    enemy->setStartPosition(this->enemyPath[0]);
    this->enemies.push_back(enemy);
}

void Game::attack()
{
    for (size_t i = 0; i < this->towers.size(); i++)
    {
        Enemy *closestEnemy = this->towers[i]->getClosestEnemy(this->enemies);

        this->towers[i]->shoot(closestEnemy);
    }
}

void Game::gameLoop()
{
    while (this->window->running())
    {
        this->updateClock();
        this->updateSelectBox();
        this->placeTower();
        this->sellTower();
        this->update();
        this->ui->handleInput();
        this->updateUI();
        this->render();
    }
}

sf::Vector2f Game::getCursorProjection()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f mapOrigin = this->levelInfo->getMapCorners()[0];
    sf::Vector2f tileSize = this->levelInfo->getMapTileSize();
    sf::Vector2f tileHalfSize = tileSize / 2.0f;
    // Convert screen coordinates to map coordinates
    sf::Vector2f mapPos = mousePosF - mapOrigin;

    // Calculate the tile coordinates
    int tileX = static_cast<int>(std::floor((mapPos.x / tileHalfSize.x + mapPos.y / tileHalfSize.y) / 2));
    int tileY = static_cast<int>(std::floor((mapPos.y / tileHalfSize.y - mapPos.x / tileHalfSize.x) / 2));

    int invertedTileY = levelInfo->getMapHeight() + tileY;
    this->currentTile = std::make_pair(tileX, invertedTileY);
    if (levelInfo->isTileBlocked(tileX, invertedTileY))
    {
        selectBox->setColor(sf::Color::Red);
        this->canPlaceTower = false;
    }
    else
    {
        selectBox->setColor(sf::Color::Green);
        this->canPlaceTower = true;
    }
    // Calculate the top-left corner of the tile
    sf::Vector2f vec = sf::Vector2f(tileX - tileY, tileX + tileY);
    sf::Vector2f tilePos;
    tilePos.x = mapOrigin.x + vec.x * tileHalfSize.x;
    tilePos.y = mapOrigin.y + vec.y * tileHalfSize.y;

    return tilePos;
}

void Game::initVariables()
{
    this->window = new WindowHandler();
    this->ui = new UI(this->window->getWindow());
    this->round = 0;
    this->endGame = false;
    this->playerHp = 100;
    this->money = 100;
    this->cursorOnMap = false;
    this->levelInfo = nullptr;
    this->selectBox = new SelectBox();
    this->canPlaceTower = false;
    this->deltaTime = 0.f;
    this->spawnTimer = 0.f;
    // this->spawnDelay = 1.f - static_cast<float>(rand() % 10) / 10; // random time 1±0.1 s
    this->spawnDelay = 1.f;
    this->nextToSpawn = -1;
}

void Game::initWorld()
{
    std::string path = "textures/level_" + std::to_string(this->level) + ".png";
    if (!this->backgroundTexture.loadFromFile(path))
    {
        std::cerr << "Error: could not load level image" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture, true);
}

bool Game::isCursorOnMap()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    sf::Vector2f p1 = this->levelInfo->getMapCorners()[0];
    sf::Vector2f p2 = this->levelInfo->getMapCorners()[1];
    sf::Vector2f p3 = this->levelInfo->getMapCorners()[2];
    sf::Vector2f p4 = this->levelInfo->getMapCorners()[3];

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

void Game::loadLevel(int level)
{
    if (this->levelInfo != nullptr)
    {
        delete this->levelInfo;
    }
    this->level = level;
    this->levelInfo = new LevelInfo(this->level);
    this->enemyPath = this->levelInfo->getPath();
    // for (auto enemy : this->levelInfo->getEnemies())
    // {
    //     for (int i = 0; i < enemy.second; i++)
    //     {
    //         this->addEnemy(enemy.first[0]);
    //     }
    // }
    this->backgroundTexture = this->levelInfo->getBackgroundTexture();
}

void Game::placeTower()
{
    if (this->isCursorOnMap() && this->canPlaceTower && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->levelInfo->isTileBlocked(this->currentTile.first, this->currentTile.second))
    {
        this->levelInfo->blockTile(this->currentTile.first, this->currentTile.second);

        Gun *gun = new MachineGun();
        sf::Vector2f pos = this->getCursorProjection();
        pos -= sf::Vector2f(0.0f, -15.0f);
        Tower *tower = new Tower(pos, 1, 100, gun);
        tower->setTile(this->currentTile.first, this->currentTile.second);

        std::cout << "Tower placed at " << tower->getTile().first << " " << tower->getTile().second << std::endl;
        std::cout << "Tower placed at " << tower->getPosition().x << " " << tower->getPosition().y << std::endl;

        this->towers.push_back(tower);
    }
}

void Game::render()
{
    std::vector<DrawableObject *> screenContent;
    if (cursorOnMap)
    {
        screenContent.push_back(selectBox);
    }
    screenContent.insert(screenContent.end(), this->enemies.begin(), this->enemies.end());
    screenContent.insert(screenContent.end(), this->towers.begin(), this->towers.end());

    sort(screenContent.begin(), screenContent.end(), [](DrawableObject *a, DrawableObject *b)
         { return a->getPosition().y < b->getPosition().y; });

    this->window->render(this->background, screenContent, ui);
}

void Game::sellTower()
{
    if (this->isCursorOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->levelInfo->isTileBlocked(this->currentTile.first, this->currentTile.second))
    {
        sf::Vector2f pos = this->getCursorProjection();
        pos -= sf::Vector2f(0.0f, -15.0f);
        for (size_t i = 0; i < this->towers.size(); i++)
        {
            std::cout << "Tower searched at " << towers[i]->getTile().first << " " << towers[i]->getTile().second << std::endl;
            if (this->towers[i]->getTile() == this->currentTile)
            {
                std::cout << "Tower removed from " << towers[i]->getTile().first << " " << towers[i]->getTile().second << std::endl;
                std::cout << "Tower removed from " << this->towers[i]->getPosition().x << " " << this->towers[i]->getPosition().y << std::endl;
                this->levelInfo->unblockTile(this->currentTile.first, this->currentTile.second);
                delete this->towers[i];
                this->towers.erase(this->towers.begin() + i);
                break;
            }
        }
    }
}

void Game::spawnEnemy()
{
    this->spawnTimer += this->deltaTime;
    if (this->spawnTimer >= this->spawnDelay)
    {
        this->spawnTimer -= this->spawnDelay;
        this->nextToSpawn++;

        if (this->nextToSpawn < this->levelInfo->getEnemiesVector().size())
        {
            this->addEnemy(this->levelInfo->getEnemiesVector()[this->nextToSpawn]);
            this->spawnDelay = 0.8f + (static_cast<float>(rand() % 10)) / 10;
        }
    }
}

void Game::update()
{
    this->window->update();
    this->spawnEnemy();

    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i]->update(this->enemyPath, this->deltaTime);
        sf::Vector2f diff = this->levelInfo->getLastPathPoint() - this->enemies[i]->getPosition();
        if (diff.x < 1.f && diff.y < 1.f)
        {
            this->playerHp -= 10;
            std::cout << "Player hp: " << this->playerHp << std::endl;
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
        }
        else if (this->enemies[i]->isDead())
        {
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            // money += 10;
        }
    }
}

void Game::updateSelectBox()
{

    if (this->isCursorOnMap())
    {
        this->selectBox->setPosition(this->getCursorProjection());
        this->cursorOnMap = true;
    }
    else
    {
        this->cursorOnMap = false;
    }
}

void Game::updateUI()
{
    this->ui->setRoundText(this->round);
    this->ui->setHealthText(this->playerHp);
    this->ui->setMoneyText(this->money);
}

//-----------------------------------
//          Public methods
//-----------------------------------

void Game::startGame()
{
    this->startingScreen();
    if (!this->window->running())
    {
        return;
    }

    this->loadLevel(1);
    this->initWorld();

    this->gameLoop();
}

void Game::startingScreen()
{
    Menu menu(this->window->getWindow());
    int choice = menu.startMenu();

    if (choice == 0) // this ensures that if "play" is selected, the game will start
    {
        return;
    }
}

void Game::updateClock()
{
    this->deltaTime = this->clock.restart().asSeconds();
}

float Game::getDeltaTime() { return this->deltaTime; }
