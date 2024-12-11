#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tower.h"
#include "gun.h"
#include "enemy.h"

Tower::Tower(sf::Vector2f position, int level, int range, std::unique_ptr<Gun> gun)
    : position(position), is_placed(position.x != -1 && position.y != -1), level(level), range(range), gun_type(std::move(gun)) {
    std::cout << "Tower initialized with " << gun_type->getType() << std::endl;
}

Tower::~Tower() {}

void Tower::placeTower(int x, int y) {
    if (is_placed) {
        std::cout << "Tower is already placed at (" << position.x << ", " << position.y << ")." << std::endl;
        return;
    }
    position = sf::Vector2f(x, y);
    is_placed = true;
    std::cout << "Tower placed at (" << x << ", " << y << ")." << std::endl;
}

void Tower::removeTower() {
    if (!is_placed) {
        std::cout << "Tower is not placed." << std::endl;
        return;
    }
    std::cout << "Tower removed from (" << position.x << ", " << position.y << ")." << std::endl;
    is_placed = false;
    position = sf::Vector2f(-1, -1);
}

sf::Vector2f Tower::getPosition() {
    return position;
}

Enemy* Tower::getClosestEnemy(const std::vector<Enemy*>& enemies) {
    Enemy* closest_enemy = nullptr;
    float min_distance = range + 1;
    for (auto enemy : enemies) {
        if (enemy->isDead()) {
            continue;
        }
        sf::Vector2f enemy_position = enemy->getPosition();
        float distance = sqrt(pow(position.x - enemy_position.x, 2) + pow(position.y - enemy_position.y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest_enemy = enemy;
        }
    }
    return closest_enemy;
}

void Tower::shoot(Enemy* enemy) {
    if (!is_placed) {
        std::cout << "Tower is not placed and cannot shoot." << std::endl;
        return;
    }
    gun_type->fire();
    if (enemy == nullptr) {
        std::cout << "No enemy in range." << std::endl;
        return;
    }
    std::cout << "Shooting to " << enemy->getType() << "located at " << enemy->getPosition().x << " " << enemy->getPosition().y << std::endl;
    enemy->takeDamage(gun_type->getDamage());
}

Tower* Tower::upgrade() {
    std::cout << "Upgrading Tower to Tower2" << std::endl;
    return new Tower2(position, level + 1, range + 10);
}

Tower2::Tower2(sf::Vector2f position, int level, int range)
    : Tower(position, level, range, std::make_unique<HighDamageGun>()) {}

Tower* Tower2::upgrade() {
    std::cout << "Upgrading Tower2 to Tower3" << std::endl;
    return new Tower3(position, level + 1, range + 10);
}

Tower3::Tower3(sf::Vector2f position, int level, int range)
    : Tower(position, level, range, std::make_unique<SniperRifle>()) {}

Tower* Tower3::upgrade() {
    std::cout << "Tower3 is the highest level and cannot be upgraded further." << std::endl;
    return this;
}