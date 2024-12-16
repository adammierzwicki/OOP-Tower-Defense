#include "enemy.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Enemy::Enemy(std::string enemy_type, int hp, float speed)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->current_path_point = 0;
}

Enemy::Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f position)
{
    this->enemy_type = enemy_type;
    this->hp = hp;
    this->speed = speed;
    this->sprite.setPosition(position);
    this->current_path_point = 0;
}

Enemy::~Enemy()
{
    // delete this->animation;
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
    this->sprite.setTextureRect(this->animation->uvRect);
}

//-----------------------------------
//          Protected methods
//-----------------------------------

void Enemy::initSprite()
{
    if (!this->texture.loadFromFile("textures/peasant_texture.png"))
    {
        std::cerr << "Error: could not load peasant texture" << std::endl;
    }
    this->animation = new Animation(&this->texture, sf::Vector2u(15, 4), 0.09f);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.4f, 0.4f);
    this->sprite.setOrigin(13.7f, 120.f);
}

//-----------------------------------
//             Accessors
//-----------------------------------

int Enemy::getHp() { return this->hp; }

int Enemy::getSpeed() { return this->speed; }

std::string Enemy::getType() { return this->enemy_type; }

sf::Vector2f Enemy::getPosition() { return this->sprite.getPosition(); }

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

void Enemy::moveAlong(std::vector<sf::Vector2f> &path)
{

    if (this->current_path_point >= path.size())
    {
        return;
    }
    sf::Vector2f direction = path[this->current_path_point] - this->sprite.getPosition();

    if (direction.x > 0 && direction.y > 0)
    {
        this->animation_row = 0;
    }
    else if (direction.x > 0 && direction.y < 0)
    {
        this->animation_row = 1;
    }
    else if (direction.x < 0 && direction.y < 0)
    {
        this->animation_row = 2;
    }
    else
    {
        this->animation_row = 3;
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

void Enemy::update(std::vector<sf::Vector2f> &path, float deltaTime)
{
    this->moveAlong(path);
    this->animate(this->animation_row, deltaTime);
}

//-----------------------------------
//              Peasant
//-----------------------------------

void Peasant::initSprite()
{
    if (!this->texture.loadFromFile("textures/peasant_texture.png"))
    {
        std::cerr << "Error: could not load peasant texture" << std::endl;
    }
    this->animation = new Animation(&this->texture, sf::Vector2u(15, 4), 0.09f);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.4f, 0.4f);
    this->sprite.setOrigin(13.7f, 120.f);

}

Peasant::Peasant() : Enemy("Peasant", 100, 0.5f)
{
    this->initSprite();
    std::cout << "Peasant created" << std::endl;
}
Peasant::~Peasant()
{
    delete this->animation;
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
