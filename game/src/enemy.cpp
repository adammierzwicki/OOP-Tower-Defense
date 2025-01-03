#include "../inc/enemy.h"

#include <iostream>

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Enemy::Enemy(std::string enemyType, int hp, float speed, int value, int damage) {
    this->initVariables();
    this->enemyType = enemyType;
    this->hp = hp;
    this->speed = speed;
    this->value = value;
    this->damage = damage;
    this->logger->log(LogLevel::DEBUG, "Enemy " + this->enemyType + " created (default constructor)", "Enemy::Enemy()", __LINE__);
}

Enemy::Enemy(std::string enemyType, int hp, float speed, int value, int damage, sf::Vector2f position) {
    this->initVariables();
    this->enemyType = enemyType;
    this->hp = hp;
    this->speed = speed;
    this->value = value;
    this->damage = damage;
    this->setStartPosition(position);
    this->logger->log(LogLevel::DEBUG, "Enemy " + this->enemyType + " created (position constructor)", "Enemy::Enemy()", __LINE__);
}

Enemy::~Enemy() {
    if (this->animation != nullptr) {
        delete this->animation;
        this->animation = nullptr;
    }
    this->logger->log(LogLevel::DEBUG, "Enemy " + this->enemyType + " destroyed", "Enemy::~Enemy()", __LINE__);
}

//-----------------------------------
//          Private methods
//-----------------------------------

void Enemy::animate(float deltaTime) {
    this->animation->update(this->animationRow, deltaTime);
    this->sprite.setTextureRect(this->animation->getUVrect());
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}

void Enemy::initVariables() {
    this->sprite = sf::Sprite();
    this->texture = sf::Texture();
    this->animation = nullptr;
    this->animationRow = 0;
    this->currentPathPoint = 0;

    this->logger = Logger::getInstance();
}

//-----------------------------------
//             Accessors
//-----------------------------------

int Enemy::getDamage() const { return this->damage; }

int Enemy::getHp() const { return this->hp; }

int Enemy::getSpeed() const { return this->speed; }

std::string Enemy::getType() const { return this->enemyType; }

sf::Vector2f Enemy::getPosition() const { return this->sprite.getPosition(); }

int Enemy::getValue() const { return this->value; }

//-----------------------------------
//             Modifiers
//-----------------------------------

void Enemy::setStartPosition(sf::Vector2f position) {
    this->sprite.setPosition(position);
}

//-----------------------------------
//          Public methods
//-----------------------------------

void Enemy::update(std::vector<sf::Vector2f>& path, float deltaTime) {
    this->moveAlong(path);
    this->animate(deltaTime);
}

void Enemy::moveAlong(std::vector<sf::Vector2f>& path) {
    if (this->currentPathPoint >= static_cast<unsigned int>(path.size())) {
        return;
    }

    sf::Vector2f direction = path[this->currentPathPoint] - this->sprite.getPosition();
    if (direction.x > 0 && direction.y > 0) {
        this->animationRow = 5;
    }
    else if (direction.x > 0 && direction.y < 0) {
        this->animationRow = 3;
    }
    else if (direction.x < 0 && direction.y < 0) {
        this->animationRow = 1;
    }
    else {
        this->animationRow = 7;
    }

    if (direction.x < 1 && direction.y < 1) {
        this->currentPathPoint++;
    }

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }

    this->sprite.setPosition(this->sprite.getPosition() + direction * this->speed);
}

void Enemy::takeDamage(int damage) {
    this->hp -= damage;
    if (this->isDead()) {
        this->logger->log(LogLevel::DEBUG, "Enemy " + this->enemyType + " died", "Enemy::takeDamage()", __LINE__);
        //! play death animation
    }
    else {
        this->logger->log(LogLevel::DEBUG, "Enemy " + this->enemyType + " took " + std::to_string(damage) + " damage", "Enemy::takeDamage()", __LINE__);
        //! play hit animation
    }
}

bool Enemy::isDead() {
    return this->hp <= 0;
}

//-----------------------------------
//              Peasant
//-----------------------------------

Peasant::Peasant() : Enemy("Peasant", 100, 0.8f, 20, 10) {
    this->initSprite();
    this->logger->log(LogLevel::DEBUG, "Peasant created", "Peasant::Peasant()", __LINE__);
}

Peasant::Peasant(bool loadTexture) : Enemy("Peasant", 100, 0.8f, 20, 10) {
    if (loadTexture) {
        this->initSprite();
    }
    this->logger->log(LogLevel::DEBUG, "Peasant " + std::string(loadTexture ? "" : "without texture") + " created", "Peasant::Peasant()", __LINE__);
}

Peasant::~Peasant() {
    if (this->animation != nullptr) {
        delete this->animation;
        this->animation = nullptr;
    }
    this->logger->log(LogLevel::DEBUG, "Peasant destroyed", "Peasant::~Peasant()", __LINE__);
}

void Peasant::initSprite() {
    if (!this->texture.loadFromFile("textures/peasant_texture.png")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load peasant texture (\"./textures/peasant_texture.png\")", "Peasant::initSprite()", __LINE__);
        throw std::runtime_error("Failed to load peasant texture");
    }
    this->animation = new Animation(&this->texture, sf::Vector2u(14, 8), 0.15f);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(60.f, 80.f);
}

//-----------------------------------
//              Warrior
//-----------------------------------

Warrior::Warrior() : Enemy("Warrior", 200, 3.f, 100, 20) {
    this->initSprite();
    this->logger->log(LogLevel::DEBUG, "Warrior created", "Warrior::Warrior()", __LINE__);
}

Warrior::~Warrior() {
    if (this->animation != nullptr) {
        delete this->animation;
        this->animation = nullptr;
    }
    this->logger->log(LogLevel::DEBUG, "Warrior destroyed", "Warrior::~Warrior()", __LINE__);
}

void Warrior::initSprite() {
    if (!this->texture.loadFromFile("textures/warrior_texture.png")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load warrior texture (\"./textures/warrior_texture.png\")", "Warrior::initSprite()", __LINE__);
        throw std::runtime_error("Failed to load warrior texture");
    }
    //! adjust animation
    this->animation = new Animation(&this->texture, sf::Vector2u(14, 8), 0.15f);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(60.f, 80.f);
}

//-----------------------------------
//            HeavyKnight
//-----------------------------------

HeavyKnight::HeavyKnight() : Enemy("HeavyKnight", 600, 1.f, 250, 50) {
    this->initSprite();
    this->logger->log(LogLevel::DEBUG, "HeavyKnight created", "HeavyKnight::HeavyKnight()", __LINE__);
}

HeavyKnight::~HeavyKnight() {
    if (this->animation != nullptr) {
        delete this->animation;
        this->animation = nullptr;
    }
    this->logger->log(LogLevel::DEBUG, "HeavyKnight destroyed", "HeavyKnight::~HeavyKnight()", __LINE__);
}

void HeavyKnight::initSprite() {
    if (!this->texture.loadFromFile("textures/heavy_texture.png")) {
        this->logger->log(LogLevel::CRITICAL, "Failed to load heavy knight texture (\"./textures/heavy_texture.png\")", "HeavyKnight::initSprite()", __LINE__);
        throw std::runtime_error("Failed to load heavy knight texture");
    }
    //! adjust animation
    this->animation = new Animation(&this->texture, sf::Vector2u(14, 8), 0.15f);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(60.f, 80.f);
}