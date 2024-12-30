#include "../inc/tower.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Tower::Tower()
{
    std::cout << "Default Tower constructor" << std::endl;
    // this->position = sf::Vector2f(-1, -1);
    // this->level = 1;
    // this->range = 100;
    // this->gun = new MachineGun();
    // this->initVariables();
    // this->initRange();
}

Tower::Tower(sf::Vector2f position, int level, int range, Gun *gun)
{
    std::cout << "Tower constructor" << std::endl;
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;
    this->initVariables();
    this->initTexture();
    this->initRange();
}

Tower::~Tower()
{
    delete this->gun;
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

Gun *Tower::getGun() const { return this->gun; }

int Tower::getLevel() const { return this->level; }

int Tower::getRange() const { return this->range; }

sf::Vector2f Tower::getPosition() const
{
    return this->sprite.getPosition();
}

void Tower::initVariables()
{
    this->shootTimer = 0.f;
}

void Tower::initTexture()
{
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(44.f, 60.f);
    this->sprite.setPosition(this->position);
    std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl; // FIXME: debug
    std::cout << this->texture.getSize().x << " " << this->texture.getSize().y << std::endl;            // FIXME: debug
}

void Tower::initRange()
{
    this->rangeCircle.setRadius(this->range);
    this->rangeCircle.setFillColor(sf::Color(255, 255, 255, 20));
    this->rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 50));
    this->rangeCircle.setOutlineThickness(2.f);
    this->rangeCircle.setOrigin(this->range, this->range);
    this->rangeCircle.setPosition(this->getPosition());
    this->rangeCircle.setScale(1.8f, 1.f);
    this->showRange = true;
}

void Tower::placeTower(std::pair<int, int> tilePosition)
{
    this->setTile(tilePosition.first, tilePosition.second);
    this->showTowerRange();
    std::cout << "Tower placed at (" << this->position.x << ", " << this->position.y << ")." << std::endl;
}

void Tower::removeTower()
{
    std::cout << "Tower removed from (" << position.x << ", " << position.y << ")." << std::endl;
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
    float delay = this->gun->getDelay();
    this->shootTimer += deltaTime;
    if (this->shootTimer >= delay)
    {
        this->shootTimer -= delay;
        if (enemy == nullptr)
        {
            std::cout << "No enemy in range." << std::endl;
            return;
        }
        gun->fire();
        std::cout << "Shooting to " << enemy->getType() << "located at " << enemy->getPosition().x << " " << enemy->getPosition().y << std::endl;
        enemy->takeDamage(gun->getDamage());
    }
}

Tower *Tower::upgrade()
{
    std::cout << "Upgrading Tower to Tower2" << std::endl;
    return new Tower2(position, level + 1, range + 10, (new Gun(*this->gun)));
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

void Tower2::initTexture()
{
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(44.f, 90.f);
    this->sprite.setPosition(this->position);
}

Tower2::Tower2(sf::Vector2f position, int level, int range, Gun *gun)
{
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;
    this->initTexture();
    this->initRange();
}
// : Tower(position, level, range, std::make_unique<HighDamageGun>()) {}

Tower *Tower2::upgrade()
{
    std::cout << "Upgrading Tower2 to Tower3" << std::endl;
    return new Tower3(position, level + 1, range + 10, (new Gun(*this->gun)));
}

//-----------------------------------
//              Tower3
//-----------------------------------

void Tower3::initTexture()
{
    std::string path = "textures/tower_" + std::to_string(level) + "_" + this->gun->getType() + ".png";
    if (!this->texture.loadFromFile(path))
    {
        std::cout << "Error: could not load tower image from file: " << path << std::endl;
    }
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(52.f, 123.f);
    this->sprite.setPosition(this->position);
}

Tower3::Tower3(sf::Vector2f position, int level, int range, Gun *gun)
{
    this->position = position;
    this->level = level;
    this->range = range;
    this->gun = gun;
    this->initTexture();
    this->initRange();
}
// : Tower(position, level, range, std::make_unique<SniperRifle>()) {}

Tower *Tower3::upgrade()
{
    std::cout << "Tower3 is the highest level and cannot be upgraded further." << std::endl;
    return this;
}