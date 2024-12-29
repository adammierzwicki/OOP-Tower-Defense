#include "../inc/tower.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Tower::Tower()
{
    this->position = sf::Vector2f(-1, -1);
    this->is_placed = false;
    this->level = 1;
    this->range = 100;
    this->gun_type = new MachineGun();
    this->initVariables();
    this->initRange();
}

Tower::Tower(sf::Vector2f position, int level, int range, Gun *gun)
{
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun_type = gun;
    this->initVariables();
    this->initRange();
    this->sprite.setOrigin(44.f, 71.f);
}

Tower::~Tower()
{
    delete this->gun_type;
}

//-----------------------------------
//          Private methods
//-----------------------------------

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (this->showRange)
    {
        target.draw(this->rangeCircle, states);
    }
    target.draw(this->sprite, states);
}

//-----------------------------------
//          Public methods
//-----------------------------------

Enemy *Tower::getClosestEnemy(const std::vector<Enemy *> &enemies)
{  
    Enemy *closest_enemy = nullptr;
    float min_distance = 2 * range; // because circle is scaled by 1.8
    for (auto enemy : enemies)
    {
        if (!this->enemyInRange(enemy))
        {
            continue;
        }
        std::cout << "Enemy in range" << std::endl;
        sf::Vector2f enemy_position = enemy->getPosition();
        float distance = sqrt(pow(position.x - enemy_position.x, 2) + pow(position.y - enemy_position.y, 2));
        if (distance < min_distance)
        {
            min_distance = distance;
            closest_enemy = enemy;
        }
    }
    return closest_enemy;
}

sf::Vector2f Tower::getPosition() const 
{   
    return this->sprite.getPosition();
}

void Tower::initVariables()
{
    if (this->level != 1){
        return;
    }
    this->is_placed = false;
    this->shootTimer = 0.f;
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun_type->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    // this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    // this->sprite.setOrigin(44.f, 71.f);
    this->sprite.setPosition(this->position);
    std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl;
    std::cout << this->texture.getSize().x << " " << this->texture.getSize().y << std::endl;
}

void Tower::initRange()
{
    this->rangeCircle.setRadius(this->range);
    this->rangeCircle.setFillColor(sf::Color(255, 255, 255, 50));
    this->rangeCircle.setOutlineColor(sf::Color::White);
    this->rangeCircle.setOutlineThickness(2.f);
    this->rangeCircle.setOrigin(this->range, this->range);
    this->rangeCircle.setPosition(this->getPosition());
    this->rangeCircle.setScale(1.8f, 1.f);
    this->showRange = true;
}


void Tower::placeTower(int x, int y)
{
    if (this->is_placed)
    {
        std::cout << "Tower is already placed at (" << this->position.x << ", " << this->position.y << ")." << std::endl;
        return;
    }
    this->position = sf::Vector2f(x, y);
    this->sprite.setPosition(this->position);
    this->is_placed = true;
    std::cout << "Tower placed at (" << this->position.x << ", " << this->position.y << ")." << std::endl;
}

void Tower::removeTower()
{
    if (!is_placed)
    {
        std::cout << "Tower is not placed." << std::endl;
        return;
    }
    std::cout << "Tower removed from (" << position.x << ", " << position.y << ")." << std::endl;
    is_placed = false;
    position = sf::Vector2f(-1, -1);
}

void Tower::setTile(int x, int y)
{
    this->occupiedTile = std::make_pair(x, y);
}

std::pair<int, int> Tower::getTile()
{
    return this->occupiedTile;
}

void Tower::shoot(Enemy *enemy, float deltaTime)
{
    float delay = this->gun_type->getDelay();
    this->shootTimer += deltaTime;
    if (this->shootTimer >= delay)
    {
        this->shootTimer -= delay;
        if (enemy == nullptr)
        {
            std::cout << "No enemy in range." << std::endl;
            return;
        }
        gun_type->fire();
        std::cout << "Shooting to " << enemy->getType() << "located at " << enemy->getPosition().x << " " << enemy->getPosition().y << std::endl;
        enemy->takeDamage(gun_type->getDamage());
    }
}

Tower *Tower::upgrade()
{
    std::cout << "Upgrading Tower to Tower2" << std::endl;
    return new Tower2(position, level + 1, range + 10, gun_type);
}

void Tower::showTowerRange() { this->showRange = true; }

void Tower::hideTowerRange() { this->showRange = false; }

bool Tower::enemyInRange(Enemy *enemy)
{
    sf::Vector2f enemy_pos = enemy->getPosition();
    sf::Vector2f tower_pos = this->getPosition();
    sf::FloatRect bds = this->rangeCircle.getGlobalBounds();
    float a = bds.width / 2;
    float b = bds.height / 2;
    if (pow(enemy_pos.x - tower_pos.x, 2) / pow(a, 2) + pow(enemy_pos.y - tower_pos.y, 2) / pow(b, 2) <= 1)
    {
        return true;
    }
    return false;
}

//-----------------------------------
//              Tower2
//-----------------------------------

void Tower2::initVariables(){
    this->is_placed = false;
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun_type->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
}

Tower2::Tower2(sf::Vector2f position, int level, int range, Gun *gun)
{
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun_type = gun;
    this->initVariables();
    this->sprite.setOrigin(44.f, 108.f);
}
// : Tower(position, level, range, std::make_unique<HighDamageGun>()) {}

Tower *Tower2::upgrade()
{
    std::cout << "Upgrading Tower2 to Tower3" << std::endl;
    return new Tower3(position, level + 1, range + 10, gun_type);
}

//-----------------------------------
//              Tower3
//-----------------------------------

void Tower3::initVariables(){
    this->is_placed = false;
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun_type->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
}

Tower3::Tower3(sf::Vector2f position, int level, int range, Gun *gun)
{
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun_type = gun;
    this->initVariables();
    this->sprite.setOrigin(51.f, 132.f);
}
// : Tower(position, level, range, std::make_unique<SniperRifle>()) {}

Tower *Tower3::upgrade()
{
    std::cout << "Tower3 is the highest level and cannot be upgraded further." << std::endl;
    return this;
}