#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "gun.h"
#include "enemy.h"

class Tower {
    protected:
        sf::Vector2f position;
        bool is_placed;
        int level;
        int range;
        std::unique_ptr<Gun> gun_type;

    public:
        Tower::Tower(sf::Vector2f position, int level, int range, std::unique_ptr<Gun> gun);

        virtual ~Tower();

        void placeTower(int x, int y);

        void removeTower();

        sf::Vector2f getPosition();

        Enemy* getClosestEnemy(const std::vector<Enemy*>& enemies);

        virtual void shoot(Enemy* enemy = nullptr);

        virtual Tower* upgrade();
};

class Tower2 : public Tower {
    public:
        Tower2::Tower2(sf::Vector2f position, int level, int range);
        Tower* upgrade() override;
};

class Tower3 : public Tower {
    public:
        Tower3::Tower3(sf::Vector2f position, int level, int range);
        Tower* upgrade() override;
};



