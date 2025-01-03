#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>

#include "../inc/endGame.h"
#include "../inc/drawableObject.h"
#include "../inc/game.h"
#include "../inc/prices.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Game::Game() {
    this->initVariables();
    this->logger->log(LogLevel::DEBUG, "Game object created", "Game::Game()", __LINE__);
}

Game::~Game() {
    delete this->window;
    delete this->ui;
    delete this->selectBox;
    delete this->levelInfo;
    for (size_t i = 0; i < this->enemies.size(); i++) {
        delete this->enemies[i];
    }
    for (size_t i = 0; i < this->towers.size(); i++) {
        delete this->towers[i];
    }
}

//-----------------------------------
//          Private methods
//-----------------------------------

void Game::initVariables() {
    this->logger = Logger::getInstance();

    this->window = new WindowHandler();

    this->ui = new UI(this->window);
    this->playerHp = 100;
    this->money = 100;
    this->round = 0;

    this->levelInfo = nullptr;
    this->endGame = false;
    this->cursorOnMap = false;
    this->isRoundStarted = false;

    this->selectBox = new SelectBox();
    this->canPlaceTower = false;
    this->newTowerChosen = false;
    this->gunType = 1;

    this->deltaTime = 0.f;
    this->spawnTimer = 0.f;
    this->spawnDelay = 1.f;
}

void Game::initWorld() {
    std::string path = "textures/level_" + std::to_string(this->level) + ".png";
    if (!this->backgroundTexture.loadFromFile(path)) {
        std::cerr << "Error: could not load level image" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture, true);
}

void Game::loadLevel(int level) {
    if (this->levelInfo != nullptr) {
        delete this->levelInfo;
    }
    this->level = level;
    this->levelInfo = new LevelInfo(this->level);
    this->enemyPath = this->levelInfo->getPath();
    this->backgroundTexture = this->levelInfo->getBackgroundTexture();
}

sf::Vector2f Game::getCursorProjection() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    sf::Vector2f mapOrigin = this->levelInfo->getMapCorners()[0];
    sf::Vector2f tileSize = this->levelInfo->getMapTileSize();
    sf::Vector2f tileHalfSize = tileSize / 2.f;

    sf::Vector2f mapPos = mousePosF - mapOrigin;

    int tileX = static_cast<int>(std::floor((mapPos.x / tileHalfSize.x + mapPos.y / tileHalfSize.y) / 2));
    int tileY = static_cast<int>(std::floor((mapPos.y / tileHalfSize.y - mapPos.x / tileHalfSize.x) / 2));

    int invertedTileY = levelInfo->getMapHeight() + tileY;
    this->currentTile = std::make_pair(tileX, invertedTileY);
    if (levelInfo->isTileBlocked(this->currentTile)) {
        selectBox->setColor(sf::Color::Red);
        this->canPlaceTower = false;
    }
    else {
        selectBox->setColor(sf::Color::Green);
        this->canPlaceTower = true;
    }

    sf::Vector2f vec = sf::Vector2f(tileX - tileY, tileX + tileY);
    sf::Vector2f tilePos;
    tilePos.x = mapOrigin.x + vec.x * tileHalfSize.x;
    tilePos.y = mapOrigin.y + vec.y * tileHalfSize.y;

    return tilePos;
}

bool Game::isCursorOnMap() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    sf::Vector2f p1 = this->levelInfo->getMapCorners()[0];
    sf::Vector2f p2 = this->levelInfo->getMapCorners()[1];
    sf::Vector2f p3 = this->levelInfo->getMapCorners()[2];
    sf::Vector2f p4 = this->levelInfo->getMapCorners()[3];

    auto sign = [](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        };

    bool b1, b2, b3, b4;

    b1 = sign(mousePosF, p1, p2) < 0.0f;
    b2 = sign(mousePosF, p2, p3) < 0.0f;
    b3 = sign(mousePosF, p3, p4) < 0.0f;
    b4 = sign(mousePosF, p4, p1) < 0.0f;

    if ((b1 == b2) && (b2 == b3) && (b3 == b4)) {
        return true;
    }
    return false;
}

void Game::gameLoop() {
    while (this->window->running()) {
        this->updateClock();
        this->interpretUIInput();
        this->update();
        this->render();

        this->isRoundOver();
        if (this->endGame) {
            break;
        }
    }
}

void Game::updateClock() {
    this->deltaTime = this->clock.restart().asSeconds();
}

void Game::update() {
    this->window->update();

    this->updateUI();
    this->updateSelectBox();
    this->updateTowers();
    if (this->isRoundStarted) {
        this->updateEnemies();
    }
}

void Game::updateUI() {
    this->ui->setRoundText(this->round + 1);
    this->ui->setHealthText(this->playerHp);
    this->ui->setMoneyText(this->money);
}

void Game::updateSelectBox() {

    if (this->isCursorOnMap()) {
        this->selectBox->setPosition(this->getCursorProjection());
        this->cursorOnMap = true;
    }
    else {
        this->cursorOnMap = false;
    }
}

void Game::updateTowers() {
    this->placeTower();
    this->sellTower();
    this->attack();
}

void Game::placeTower() {
    if (this->isCursorOnMap() && this->canPlaceTower && this->newTowerChosen && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->levelInfo->isTileBlocked(this->currentTile)) {
        this->levelInfo->blockTile(this->currentTile);
        this->newTowerChosen = false;

        Gun* gun = nullptr;
        switch (this->gunType) {
        case 1:
            gun = new MachineGun();
            this->money -= Prices::machineGunTower;
            break;
        case 2:
            gun = new HighDamageGun();
            this->money -= Prices::highDamageTower;
            break;
        case 3:
            gun = new SniperRifle();
            this->money -= Prices::sniperTower;
            break;
        }
        sf::Vector2f pos = this->getCursorProjection();
        Tower* tower = new Tower(pos, 1, 100, gun);
        tower->placeTower(this->currentTile);

        this->towers.push_back(tower);
    }
}

void Game::sellTower() {
    if (this->isCursorOnMap() && sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->levelInfo->isTileBlocked(this->currentTile)) {
        this->getCursorProjection();

        for (size_t i = 0; i < this->towers.size(); i++) {
            if (this->towers[i]->getTile() == this->currentTile) {
                this->levelInfo->unblockTile(this->currentTile);

                char gunType = this->towers[i]->getGun()->getType();
                switch (gunType) {
                case 'm':
                    this->money += Prices::machineGunTower / 2;
                    break;
                case 'h':
                    this->money += Prices::highDamageTower / 2;
                    break;
                case 's':
                    this->money += Prices::sniperTower / 2;
                    break;
                }

                delete this->towers[i];
                this->towers.erase(this->towers.begin() + i);

                this->logger->log(LogLevel::DEBUG, "Tower removed from (" + std::to_string(this->currentTile.first) + ", " + std::to_string(this->currentTile.second) + ")", "Game::sellTower()", __LINE__);
                break;
            }
        }
    }
}

void Game::attack() {
    for (size_t i = 0; i < this->towers.size(); i++) {
        Enemy* closestEnemy = this->towers[i]->getClosestEnemy(this->enemies);

        if (closestEnemy != nullptr) {
            this->towers[i]->shoot(closestEnemy, this->deltaTime);
        }
    }
}

void Game::updateEnemies() {
    this->spawnEnemy();

    for (size_t i = 0; i < this->enemies.size(); i++) {
        this->enemies[i]->update(this->enemyPath, this->deltaTime);

        sf::Vector2f diff = this->levelInfo->getLastPathPoint() - this->enemies[i]->getPosition();
        if (diff.x < 1.f && diff.y < 1.f) {
            this->playerHp -= enemies[i]->getDamage();
            this->logger->log(LogLevel::INFO, "Player lost " + std::to_string(enemies[i]->getDamage()) + " hp", "Game::updateEnemies()", __LINE__);

            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
        }
        else if (this->enemies[i]->isDead()) {
            money += this->enemies[i]->getValue();

            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::spawnEnemy() {
    this->spawnTimer += this->deltaTime;
    if (this->spawnTimer >= this->spawnDelay) {
        this->spawnTimer -= this->spawnDelay;
        if (this->levelInfo->hasNextEnemy(this->round)) {
            this->addEnemy(this->levelInfo->getNextEnemy(this->round));
            this->spawnDelay = 0.8f + (static_cast<float>(rand() % 10)) / 10;
        }
    }
}

void Game::addEnemy(char enemyType) {
    Enemy* enemy = nullptr;
    switch (enemyType) {
    case 'P':
        enemy = new Peasant(true);
        break;
    case 'W':
        enemy = new Warrior();
        break;
    case 'H':
        enemy = new HeavyKnight();
        break;
    }
    if (enemy == nullptr) {
        this->logger->log(LogLevel::CRITICAL, "Enemy type not recognized", "Game::addEnemy()", __LINE__);
        throw std::runtime_error("Enemy type not recognized");
    }

    enemy->setStartPosition(this->enemyPath[0]);
    this->enemies.push_back(enemy);

    this->logger->log(LogLevel::DEBUG, "Added enemy " + enemy->getType(), "Game::addEnemy()", __LINE__);
}

void Game::interpretUIInput() {
    ButtonType button = this->ui->handleInput();
    switch (button) {
    case ButtonType::MACHINE_GUN:
        if (this->money < Prices::machineGunTower) {
            this->logger->log(LogLevel::INFO, "Not enough money");
            break;
        }
        this->gunType = 1;
        this->newTowerChosen = true;
        break;
    case ButtonType::HIGH_DAMAGE_GUN:
        if (this->money < Prices::highDamageTower) {
            this->logger->log(LogLevel::INFO, "Not enough money");
            break;
        }
        this->gunType = 2;
        this->newTowerChosen = true;
        break;
    case ButtonType::SNIPER_RIFLE:
        if (this->money < Prices::sniperTower) {
            this->logger->log(LogLevel::INFO, "Not enough money");
            break;
        }
        this->gunType = 3;
        this->newTowerChosen = true;
        break;
    case ButtonType::START_GAME:
        this->isRoundStarted = true;
        break;
    case ButtonType::UPGRADE:
        if (this->money < Prices::upgrade) {
            this->logger->log(LogLevel::INFO, "Not enough money");
            break;
        }
        for (size_t i = 0; i < this->towers.size(); i++) {
            Tower* newTower = this->towers[i]->upgrade();
            if (newTower != towers[i]) {
                delete this->towers[i];
                this->towers[i] = newTower;
            }
        }
        this->money -= Prices::upgrade;
        break;
    default:
        break;
    }
}

void Game::render() {
    std::vector<DrawableObject*> screenContent;
    if (cursorOnMap && newTowerChosen) {
        screenContent.push_back(selectBox);
    }
    screenContent.insert(screenContent.end(), this->enemies.begin(), this->enemies.end());
    screenContent.insert(screenContent.end(), this->towers.begin(), this->towers.end());

    sort(screenContent.begin(), screenContent.end(), [](DrawableObject* a, DrawableObject* b) { return a->getPosition().y < b->getPosition().y; });

    this->window->render(this->background, screenContent, ui);
}

void Game::isRoundOver() {
    if (this->playerHp <= 0 || this->round == this->levelInfo->getRoundsCount()) {
        this->endGame = true;
    }

    if (this->enemies.size() == 0 && !this->levelInfo->hasNextEnemy(this->round) && this->isRoundStarted) {
        this->logger->log(LogLevel::INFO, "Round ended");

        this->round++;
        this->money += 200;
        this->isRoundStarted = false;
    }
}

void Game::endingScreen() {
    std::string message;
    if (this->playerHp <= 0) {
        message = "You lost!";
    }
    else if (this->round == this->levelInfo->getRoundsCount()) {
        message = "You won!";
    }

    if (!message.empty()) {
        EndGame endGame(this->window->getWindow(), message);
        bool isRunning = true;
        while (isRunning && this->window->running()) {
            endGame.handleInput(isRunning);
            endGame.render();
        }

        this->logger->log(LogLevel::INFO, "Game ended. " + message);
    }
}

void Game::autosave() {
    std::ofstream file;
    file.open("autosave.txt");
    file << *this;
    file.close();
    this->logger->log(LogLevel::INFO, "Game saved");
}

//! get rid of initialPos, load from beginning of round
void Game::loadSave() {
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
    int towersCount = std::stoi(line.substr(8));
    for (int i = 0; i < towersCount; i++) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string levelStr, gunStr, rangeStr, xStr, yStr;
        iss >> levelStr >> gunStr >> rangeStr >> xStr >> yStr;
        int level = std::stoi(levelStr);
        int range = std::stoi(rangeStr);
        int x = std::stoi(xStr);
        int y = std::stoi(yStr);
        Gun* gun = nullptr;
        switch (gunStr[0]) {
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
        Tower* tower = new Tower(sf::Vector2f(x, y), level, range, gun);
        this->towers.push_back(tower);
    }
    file.close();
}

//-----------------------------------
//             Accessors
//-----------------------------------

float Game::getDeltaTime() { return this->deltaTime; }

int Game::getLevel() const { return this->level; }

int Game::getRound() const { return this->round; }

int Game::getPlayerHp() const { return this->playerHp; }

int Game::getMoney() const { return this->money; }

std::vector<Enemy*> Game::getEnemies() const { return this->enemies; }

std::vector<Tower*> Game::getTowers() const { return this->towers; }

//-----------------------------------
//          Public methods
//-----------------------------------

std::ostream& operator<<(std::ostream& os, const Game& game) {
    time_t now;
    time(&now);
    os << "Autosave from " << ctime(&now) << "\n";
    os << "Level: " << game.getLevel() << "\n";
    os << "Round: " << game.getRound() << "\n";
    os << "Player HP: " << game.getPlayerHp() << "\n";
    os << "Money: " << game.getMoney() << "\n";
    os << "Towers: " << game.getTowers().size() << "\n";
    for (size_t i = 0; i < game.getTowers().size(); i++) {
        os << game.getTowers()[i]->getLevel() << " " << game.getTowers()[i]->getGun()->getName() << " " << game.getTowers()[i]->getRange() << " " << game.getTowers()[i]->getPosition().x << " " << game.getTowers()[i]->getPosition().y << "\n";
    }
    return os;
}

void Game::startingScreen() {
    Menu menu(this->window->getWindow());
    int choice = menu.startMenu();

    if (choice == 0) {
        return;
    }
}

void Game::startGame() {
    this->startingScreen();
    if (!this->window->running()) {
        return;
    }
    // std::ifstream infile("autosave.txt");
    // if (infile.good())
    // {
    //     std::cout << "Loading game from save..." << std::endl;
    //     this->loadSave();
    //     this->loadLevel(this->level);
    //     this->isRoundStarted = true;
    // }
    // else
    // {
    //     std::cout << "No save found. Starting new game..." << std::endl;
    //     this->loadLevel(1);
    // }
    this->loadLevel(1);
    this->initWorld();

    this->gameLoop();

    this->endingScreen();

    if (!endGame) {
        this->autosave();
    }
}