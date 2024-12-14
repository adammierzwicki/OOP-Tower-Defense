#include "enemy.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Enemy::Enemy(std::string enemy_type, int hp, float speed)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->position = sf::Vector2f(0.f, 0.f);
}

Enemy::Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f position)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->position = position;
    this->shape.setPosition(position);
}

Enemy::~Enemy()
{
    std::cout << "Enemy destroyed" << std::endl;
}

//-----------------------------------
//          Protected methods
//-----------------------------------

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}

void Enemy::initShape()
{
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

//-----------------------------------
//             Accessors
//-----------------------------------

int Enemy::getHp() { return this->hp; }

int Enemy::getSpeed() { return this->speed; }

std::string Enemy::getType() { return this->enemy_type; }

sf::Vector2f Enemy::getPosition() { return this->position; }

//-----------------------------------
//             Modifiers
//-----------------------------------

void Enemy::setStartPosition(sf::Vector2f position) 
{
    this->position = position;
    this->shape.setPosition(position);
}

//-----------------------------------
//          Public methods
//-----------------------------------

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

bool Enemy::isDead()
{
    return this->hp <= 0;
}

void Enemy::update()
{
    // todo: move enemy along path
}

//-----------------------------------
//              Peasant
//-----------------------------------

void Peasant::initShape()
{
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Peasant::Peasant() : Enemy("Peasant", 100, 2.f)
{
    this->initShape();
    std::cout << "Peasant created" << std::endl;
}
Peasant::~Peasant()
{
    std::cout << "Peasant destroyed" << std::endl;
}

//-----------------------------------
//              Warrior
//-----------------------------------

Warrior::Warrior() : Enemy("Warrior", 200, 5.f)
{
    std::cout << "Warrior created" << std::endl;
}

Warrior::~Warrior()
{
    std::cout << "Warrior destroyed" << std::endl;
}

//-----------------------------------
//            HeavyKnight
//-----------------------------------

HeavyKnight::HeavyKnight() : Enemy("HeavyKnight", 600, 1.f)
{
    std::cout << "HeavyKnight created" << std::endl;
}

HeavyKnight::~HeavyKnight()
{
    std::cout << "HeavyKnight destroyed" << std::endl;
}
