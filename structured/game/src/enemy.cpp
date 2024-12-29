#include <iostream>
#include "../inc/enemy.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Enemy::Enemy(std::string enemy_type, int hp, float speed)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->current_path_point = 0;
    this->animation = nullptr;
}
Enemy::Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f position)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->sprite.setPosition(position);
    this->current_path_point = 0;
    this->animation = nullptr;
}

Enemy::~Enemy()
{
    if (this->animation != nullptr)
    {
        delete this->animation;
        this->animation = nullptr;
    }
    std::cout << "Enemy destroyed" << std::endl;
}

//-----------------------------------
//          Private methods
//-----------------------------------

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->sprite, states);
}

void Enemy::animate(int row, float deltaTime)
{
    this->animation->update(row, deltaTime);
    this->sprite.setTextureRect(this->animation->getUVrect());
}

//-----------------------------------
//             Accessors
//-----------------------------------

int Enemy::getHp() const { return this->hp; }

int Enemy::getSpeed() const { return this->speed; }

std::string Enemy::getType() const { return this->enemy_type; }

sf::Vector2f Enemy::getPosition() const {
    return this->sprite.getPosition(); }

//-----------------------------------
//             Modifiers
//-----------------------------------

void Enemy::setStartPosition(sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

//-----------------------------------
//          Public methods
//-----------------------------------

bool Enemy::isDead()
{
    return this->hp <= 0;
}

void Enemy::moveAlong(std::vector<sf::Vector2f> &path)
{
    if (this->current_path_point >= path.size())
    {
        return;
    }

    sf::Vector2f direction = path[this->current_path_point] - this->sprite.getPosition();
    // if (direction.x > 0 && direction.y > 0)
    // {
    //     this->animation_row = 0;
    // }
    // else if (direction.x > 0 && direction.y < 0)
    // {
    //     this->animation_row = 1;
    // }
    // else if (direction.x < 0 && direction.y < 0)
    // {
    //     this->animation_row = 2;
    // }
    // else
    // {
    //     this->animation_row = 3;
    // }
    if (direction.x > 0 && direction.y > 0)
    {
        this->animation_row = 5;
    }
    else if (direction.x > 0 && direction.y < 0)
    {
        this->animation_row = 3;
    }
    else if (direction.x < 0 && direction.y < 0)
    {
        this->animation_row = 1;
    }
    else
    {
        this->animation_row = 7;
    }

    if (direction.x < 1 && direction.y < 1)
    {
        this->current_path_point++;
    }

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }
    this->sprite.setPosition(this->sprite.getPosition() + direction * this->speed);
}

void Enemy::takeDamage(int damage)
{
    this->hp -= damage;
    if (this->isDead())
    {
        std::cout << "Enemy died" << std::endl;
        // todo: remove from screen and queue
    }
    else
    {
        std::cout << "Enemy takes " << damage << " damage" << std::endl;
    }
}

void Enemy::update(std::vector<sf::Vector2f> &path, float deltaTime)
{
    this->moveAlong(path);
    this->animate(this->animation_row, deltaTime);
}

//-----------------------------------
//              Peasant
//-----------------------------------

Peasant::Peasant() : Enemy("Peasant", 100, 0.8f)
{
    this->initSprite();
    std::cout << "Peasant created" << std::endl;
}

Peasant::~Peasant()
{
    if (this->animation != nullptr)
    {
        delete this->animation;
        this->animation = nullptr;
    }
    std::cout << "Peasant destroyed" << std::endl;
}

void Peasant::initSprite()
{
    if (!this->texture.loadFromFile("textures/peasant_texture.png"))
    {
        throw std::runtime_error("Unable to load peasant texture");
    }
    // this->animation = new Animation(&this->texture, sf::Vector2u(15, 4), 0.09f);
    this->animation = new Animation(&this->texture, sf::Vector2u(14, 8), 0.15f);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(1.f, 1.f);
    this->sprite.setOrigin(60.f, 80.f);
    // this->sprite.setScale(0.4f, 0.4f);
    // this->sprite.setOrigin(13.7f, 120.f);
}

//-----------------------------------
//              Warrior
//-----------------------------------

Warrior::Warrior() : Enemy("Warrior", 200, 5.f)
{
    this->initSprite();
    std::cout << "Warrior created" << std::endl;
}

Warrior::~Warrior()
{
    if (this->animation != nullptr)
    {
        delete this->animation;
        this->animation = nullptr;
    }
    std::cout << "Warrior destroyed" << std::endl;
}

void Warrior::initSprite()
{
    if (!this->texture.loadFromFile("textures/warrior_texture.png"))
    {
        throw std::runtime_error("Unable to load warrior texture");
    }
    // TODO change values after adding texture
    this->animation = new Animation(&this->texture, sf::Vector2u(15, 4), 0.09f);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.4f, 0.4f);
    this->sprite.setOrigin(13.7f, 120.f);
}

//-----------------------------------
//            HeavyKnight
//-----------------------------------

HeavyKnight::HeavyKnight() : Enemy("HeavyKnight", 600, 1.f)
{
    this->initSprite();
    std::cout << "HeavyKnight created" << std::endl;
}

HeavyKnight::~HeavyKnight()
{
    if (this->animation != nullptr)
    {
        delete this->animation;
        this->animation = nullptr;
    }
    std::cout << "HeavyKnight destroyed" << std::endl;
}

void HeavyKnight::initSprite()
{
    if (!this->texture.loadFromFile("textures/heavy_texture.png"))
    {
        throw std::runtime_error("Unable to load heavy knight texture");
    }
    // TODO change values after adding texture
    this->animation = new Animation(&this->texture, sf::Vector2u(15, 4), 0.09f);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.4f, 0.4f);
    this->sprite.setOrigin(13.7f, 120.f);
}