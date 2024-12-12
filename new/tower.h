#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "gun.h"

#ifndef ENEMY_H
#define ENEMY_H
#include "enemy.h"
#endif

class Tower : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

protected:
    sf::Vector2f position;
    bool is_placed;
    int level;
    int range;
    // todo: why?
    //  std::unique_ptr<Gun> gun_type;
    Gun *gun_type;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Tower();
    // Tower(sf::Vector2f position, int level, int range, std::unique_ptr<Gun> gun);
    Tower(sf::Vector2f position, int level, int range, Gun *gun);

    virtual ~Tower();

    void initVariables();

    void placeTower(int x, int y);

    void removeTower();

    sf::Vector2f getPosition();

    Enemy *getClosestEnemy(const std::vector<Enemy *> &enemies);

    virtual void shoot(Enemy *enemy = nullptr);

    virtual Tower *upgrade();
};

class Tower2 : public Tower
{
public:
    Tower2(sf::Vector2f position, int level, int range);
    Tower *upgrade() override;
};

class Tower3 : public Tower
{
public:
    Tower3(sf::Vector2f position, int level, int range);
    Tower *upgrade() override;
};
