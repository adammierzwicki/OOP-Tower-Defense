#include "../inc/tower.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Tower::Tower() {
    this->logger = Logger::getInstance();
    this->logger->log(LogLevel::DEBUG, "Default Tower constructor", "Tower::Tower()", __LINE__);
    this->initVariables();
}

Tower::Tower(sf::Vector2f position, int level, int range, Gun* gun) {
    this->logger = Logger::getInstance();
    this->logger->log(LogLevel::DEBUG, "Tower constructor", "Tower::Tower()", __LINE__);

    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;

    this->initVariables();
    this->initTexture();
    this->initRange();
}

Tower::~Tower() {
    delete this->gun;
}

//-----------------------------------
//          Private methods
//-----------------------------------

void Tower::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (this->showRange) {
        target.draw(this->rangeCircle, states);
    }
    target.draw(this->sprite, states);
}

//-----------------------------------
//         Protected methods
//-----------------------------------

void Tower::initRange() {
    this->rangeCircle.setRadius(this->range);
    this->rangeCircle.setFillColor(sf::Color(255, 255, 255, 20));
    this->rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 50));
    this->rangeCircle.setOutlineThickness(2.f);
    this->rangeCircle.setOrigin(this->range, this->range);
    this->rangeCircle.setPosition(this->position);
    this->rangeCircle.setScale(1.8f, 1.f);
    this->showRange = true;
}

void Tower::initVariables() {
    this->shootTimer = 0.f;
}

void Tower::initTexture() {
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getName() + ".png";
    if (!this->texture.loadFromFile(path)) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load tower texture (\"./" + path + "\")", "Tower::initTexture()", __LINE__);
        throw std::runtime_error("Failed to load tower texture");
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(44.f, 60.f);
    this->sprite.setPosition(this->position);
}

//-----------------------------------
//             Accessors
//-----------------------------------

Gun* Tower::getGun() const { return this->gun; }

int Tower::getLevel() const { return this->level; }

sf::Vector2f Tower::getPosition() const { return this->position; }

int Tower::getRange() const { return this->range; }

sf::CircleShape* Tower::getRangeCircle() { return &this->rangeCircle; }

std::pair<int, int> Tower::getTile() { return this->occupiedTile; }

//-----------------------------------
//             Modifiers
//-----------------------------------

void Tower::setPosition(sf::Vector2f pos) {
    this->position = pos;
    this->sprite.setPosition(pos);
}

void Tower::setRange(int range) {
    this->range = range;
}

void Tower::setTile(int x, int y) {
    this->occupiedTile = std::make_pair(x, y);
}

//-----------------------------------
//          Public methods
//-----------------------------------

bool Tower::enemyInRange(Enemy* enemy) {
    sf::Vector2f enemy_pos = enemy->getPosition();
    sf::FloatRect bounds = this->rangeCircle.getGlobalBounds();
    float a = bounds.width / 2;
    float b = bounds.height / 2;

    if (pow(enemy_pos.x - this->position.x, 2) / pow(a, 2) + pow(enemy_pos.y - this->position.y, 2) / pow(b, 2) <= 1) {
        return true;
    }
    return false;
}

Enemy* Tower::getClosestEnemy(const std::vector<Enemy*>& enemies) {
    Enemy* closest_enemy = nullptr;
    float min_distance = 2 * range;
    for (auto enemy : enemies) {
        if (!this->enemyInRange(enemy)) {
            continue;
        }
        sf::Vector2f enemy_position = enemy->getPosition();
        float distance = sqrt(pow(this->position.x - enemy_position.x, 2) + pow(this->position.y - enemy_position.y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest_enemy = enemy;
        }
    }
    return closest_enemy;
}

void Tower::placeTower(std::pair<int, int> tilePosition) {
    this->setTile(tilePosition.first, tilePosition.second);
    this->showTowerRange();
    this->logger->log(LogLevel::DEBUG, "Tower placed at (" + std::to_string(this->position.x) + ", " + std::to_string(this->position.y) + ")", "Tower::placeTower()", __LINE__);
}

void Tower::removeTower() {
    this->logger->log(LogLevel::DEBUG, "Tower removed from (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")", "Tower::removeTower()", __LINE__);
    position = sf::Vector2f(-1, -1);
}

void Tower::shoot(Enemy* enemy, float deltaTime) {
    float delay = this->gun->getDelay();
    this->shootTimer += deltaTime;
    if (this->shootTimer >= delay) {
        this->shootTimer -= delay;
        if (enemy == nullptr) {
            return;
        }
        gun->fire();
        enemy->takeDamage(gun->getDamage());
        this->logger->log(LogLevel::DEBUG, "Shoot at " + enemy->getType() + " @ (" + std::to_string(enemy->getPosition().x) + ", " + std::to_string(enemy->getPosition().y) + ")", "Tower::shoot()", __LINE__);
    }
}

void Tower::showTowerRange() { this->showRange = true; }

void Tower::hideTowerRange() { this->showRange = false; }

Tower* Tower::upgrade() {
    this->logger->log(LogLevel::DEBUG, "Upgrading Tower1 to Tower2", "Tower::upgrade()", __LINE__);
    Tower2* t = new Tower2(position, level + 1, range + 10, (new Gun(*this->gun)));
    t->setTile(this->occupiedTile.first, this->occupiedTile.second);
    return t;
}

//-----------------------------------
//              Tower2
//-----------------------------------

void Tower2::initTexture() {
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getName() + ".png";
    if (!this->texture.loadFromFile(path)) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load tower texture (\"./" + path + "\")", "Tower2::initTexture()", __LINE__);
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(44.f, 90.f);
    this->sprite.setPosition(this->position);
}

Tower2::Tower2(sf::Vector2f position, int level, int range, Gun* gun) {
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;
    this->initTexture();
    this->initRange();
}

Tower* Tower2::upgrade() {
    this->logger->log(LogLevel::DEBUG, "Upgrading Tower2 to Tower3", "Tower2::upgrade()", __LINE__);
    Tower3* t = new Tower3(position, level + 1, range + 10, (new Gun(*this->gun)));
    t->setTile(this->occupiedTile.first, this->occupiedTile.second);
    return t;
}

//-----------------------------------
//              Tower3
//-----------------------------------

void Tower3::initTexture() {
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getName() + ".png";
    if (!this->texture.loadFromFile(path)) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load tower texture (\"./" + path + "\")", "Tower3::initTexture()", __LINE__);
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(52.f, 123.f);
    this->sprite.setPosition(this->position);
}

Tower3::Tower3(sf::Vector2f position, int level, int range, Gun* gun) {
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;
    this->initTexture();
    this->initRange();
}

Tower* Tower3::upgrade() {
    this->logger->log(LogLevel::DEBUG, "Upgrading Tower3: Unable to upgrade further", "Tower3::upgrade()", __LINE__);
    return this;
}