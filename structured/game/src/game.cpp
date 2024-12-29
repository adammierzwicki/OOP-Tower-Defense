#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream>

#include "../inc/drawableObject.h"
#include "../inc/game.h"
// #include "../inc/ui.h"

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

void Game::addEnemy(char enemyType, sf::Vector2f initialPos = {-1.f, -1.f})
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
    if (initialPos != sf::Vector2f(-1.f, -1.f))
    {
        enemy->setStartPosition(initialPos);
    }
    else
    {
        enemy->setStartPosition(this->enemyPath[0]);
    }
    this->enemies.push_back(enemy);
}

void Game::attack()
{
    for (size_t i = 0; i < this->towers.size(); i++)
    {
        Enemy *closestEnemy = this->towers[i]->getClosestEnemy(this->enemies);
        if (closestEnemy != nullptr)
            this->towers[i]->shoot(closestEnemy, this->deltaTime);
    }
}

void Game::autosave()
{
    std::ofstream file;
    file.open("autosave.txt");
    file << *this;
    file.close();
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
        this->attack();
        this->interpretUIInput();
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
    this->ui = new UI(this->window);
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
    this->isRoundStarted = false;
    this->gunType = 1;
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
        Gun *gun = nullptr;
        switch (this->gunType)
        {
            case 1:
                gun = new MachineGun();
                break;
            case 2:
                gun = new HighDamageGun();
                break;
            case 3:
                gun = new SniperRifle();
                break;
        }
        // Gun *gun = new MachineGun();
        sf::Vector2f pos = this->getCursorProjection();
        pos -= sf::Vector2f(0.0f, -15.0f);
        Tower *tower = new Tower(pos, 1, 100, gun);
        tower->setTile(this->currentTile.first, this->currentTile.second);
        tower->showTowerRange();
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

        if (this->nextToSpawn < this->levelInfo->getEnemiesVector(this->round).size())
        {
            this->addEnemy(this->levelInfo->getEnemiesVector(this->round)[this->nextToSpawn]);
            this->spawnDelay = 0.8f + (static_cast<float>(rand() % 10)) / 10;
        }
    }
}

void Game::update()
{
    this->window->update();
    if (this->isRoundStarted){
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

void Game::interpretUIInput()
{
    ButtonType button = this->ui->handleInput();
    switch (button)
    {
        case ButtonType::MACHINE_GUN:
            this->gunType = 1;
            break;
        case ButtonType::HIGH_DAMAGE_GUN:
            this->gunType = 2;
            break;
        case ButtonType::SNIPER_RIFLE:
            this->gunType = 3;
            break;
        case ButtonType::START_GAME:
            this->isRoundStarted = true;
            break;
        case ButtonType::UPGRADE:
            for (size_t i = 0; i < this->towers.size(); i++)
            {
                Tower *newTower = this->towers[i]->upgrade();
                if (newTower != towers[i])
                {
                    // delete this->towers[i];
                    this->towers[i] = newTower;
                }
            }
            break;
        default:
            break;
    }
}

void Game::loadSave()
{
    std::ifstream file("autosave.txt");
    std::string line;
    std::getline(file, line); // skip title
    std::getline(file, line); // skip blank
    std::getline(file, line);
    this->level = std::stoi(line.substr(7));
    std::getline(file, line);
    this->round = std::stoi(line.substr(7));
    std::getline(file, line);
    this->playerHp = std::stoi(line.substr(11));
    std::getline(file, line);
    this->money = std::stoi(line.substr(7));
    std::getline(file, line);
    int enemiesCount = std::stoi(line.substr(9));
    for (int i = 0; i < enemiesCount; i++)
    {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string typeStr, xStr, yStr;
        iss >> typeStr >> xStr >> yStr;
        char type = typeStr[0];
        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        this->addEnemy(type, sf::Vector2f(x, y));
    }
    std::getline(file, line);
    int towersCount = std::stoi(line.substr(8));
    for (int i = 0; i < towersCount; i++)
    {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string levelStr, gunStr, rangeStr, xStr, yStr;
        iss >> levelStr >> gunStr >> rangeStr >> xStr >> yStr;
        int level = std::stoi(levelStr);
        int range = std::stoi(rangeStr);
        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        Gun *gun = nullptr;
        switch (gunStr[0])
        {
        case 'm':
            gun = new MachineGun();
            break;
        case 'h':
            gun = new HighDamageGun();
            break;
        case 's':
            gun = new SniperRifle();
            break;
        }
        Tower *tower = new Tower(sf::Vector2f(x, y), level, range, gun);
        this->towers.push_back(tower);
    }
    file.close();
}

//-----------------------------------
//          Public methods
//-----------------------------------

std::ostream& operator<<(std::ostream& os, const Game& game)
{   
    time_t now;
    time(&now);   
    os << "Autosave from " << ctime(&now) << "\n";
    os << "Level: " << game.getLevel() << "\n";
    os << "Round: " << game.getRound() << "\n";
    os << "Player HP: " << game.getPlayerHp() << "\n";
    os << "Money: " << game.getMoney() << "\n";
    os << "Enemies: " << game.getEnemies().size() << "\n";
    for (size_t i = 0; i < game.getEnemies().size(); i++)
    {
        os << game.getEnemies()[i]->getType() << " " << game.getEnemies()[i]->getPosition().x << " " << game.getEnemies()[i]->getPosition().y << "\n";
    }
    os << "Towers: " << game.getTowers().size() << "\n";
    for (size_t i = 0; i < game.getTowers().size(); i++)
    {
        os << game.getTowers()[i]->getLevel() << " " << game.getTowers()[i]->getGun()->getType() << " " << game.getTowers()[i]->getRange() << " " << game.getTowers()[i]->getPosition().x << " " << game.getTowers()[i]->getPosition().y << "\n";
    }
    return os;
}

int Game::getLevel() const { return this->level; }

int Game::getRound() const { return this->round; }

int Game::getPlayerHp() const { return this->playerHp; }

int Game::getMoney() const { return this->money; }

std::vector<Enemy *> Game::getEnemies() const { return this->enemies; }

std::vector<Tower *> Game::getTowers() const { return this->towers; }

void Game::startGame()
{
    this->startingScreen();
    if (!this->window->running())
    {
        return;
    }
    // std::ifstream infile("autosave.txt");
    // if (infile.good())
    // {
    //     std::cout << "Autosave file exists. Loading game state..." << std::endl;
    //     this->loadSave();
    //     this->loadLevel(this->level);
    //     this->isRoundStarted = true;
    // }
    // else
    // {
    //     std::cout << "No autosave file found. Starting a new game..." << std::endl;
    //     this->loadLevel(1);
    // }
    this->loadLevel(1);
    this->initWorld();


    this->gameLoop();
    this->autosave();
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
