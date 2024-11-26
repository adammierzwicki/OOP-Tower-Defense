#include <iostream>
#include <memory>
#include <vector>
#include "gun.cpp"
#include "enemy.cpp"


class Tower {
    protected:
        std::pair<int, int> position;
        bool is_placed;
        int level;
        int range;
        std::unique_ptr<Gun> gun_type;

    public:
        Tower(std::pair<int, int> position = std::make_pair(-1, -1), int level = 1, int range = 10, std::unique_ptr<Gun> gun = std::make_unique<MachineGun>())
            : position(position), is_placed(position.first != -1 && position.second != -1), level(level), range(range), gun_type(std::move(gun)) {
            std::cout << "Tower initialized with " << gun_type->getType() << std::endl;
        }

        virtual ~Tower() {}

        void placeTower(int x, int y) {
            if (is_placed) {
                std::cout << "Tower is already placed at (" << position.first << ", " << position.second << ")." << std::endl;
                return;
            }
            position = std::make_pair(x, y);
            is_placed = true;
            std::cout << "Tower placed at (" << x << ", " << y << ")." << std::endl;
        }

        void removeTower() {
            if (!is_placed) {
                std::cout << "Tower is not placed." << std::endl;
                return;
            }
            std::cout << "Tower removed from (" << position.first << ", " << position.second << ")." << std::endl;
            is_placed = false;
            position = std::make_pair(-1, -1);
        }

        std::pair<int, int> getPosition() {
            return position;
        }

        //have to check if this is working
        Enemy* getClosestEnemy(const std::vector<Enemy*>& enemies) {
            Enemy* closest_enemy = nullptr;
            float min_distance = range + 1;
            for (auto enemy : enemies) {
                if (enemy->isDead()) {
                    continue;
                }
                std::pair<int, int> enemy_position = enemy->getPosition();
                float distance = sqrt(pow(position.first - enemy_position.first, 2) + pow(position.second - enemy_position.second, 2));
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_enemy = enemy;
                }
            }
            return closest_enemy;
        }
        
        //TODO: change according to description below
        virtual void shoot(Enemy* enemy = nullptr) {
            if (!is_placed) {
                std::cout << "Tower is not placed and cannot shoot." << std::endl;
                return;
            }
            gun_type->fire();
            // here would be nice to add some choosing of closest enemy instead of passing it as an argument
            // we can implement some kind of wave class which will hold a vector of all enemies
            if (enemy == nullptr) {
                std::cout << "No enemy in range." << std::endl;
                return;
            }
            std::cout << "Shooting to " << enemy->getType() << "located at " << enemy->getPosition().first << " " << enemy->getPosition().second << std::endl;
            enemy->takeDamage(gun_type->getDamage());

        }

        virtual Tower* upgrade(); // here I only declare this funciton, because the compiler will not see Tower 2 yet
};

class Tower2 : public Tower {
    public:
        Tower2(std::pair<int, int> position = std::make_pair(-1, -1), int level = 2, int range = 15)
            : Tower(position, level, range, std::make_unique<HighDamageGun>()) {}

        Tower* upgrade() override;
};

class Tower3 : public Tower {
    public:
        Tower3(std::pair<int, int> position = std::make_pair(-1, -1), int level = 3, int range = 25)
            : Tower(position, level, range, std::make_unique<SniperRifle>()) {}

        Tower* upgrade() override {
            std::cout << "Tower3 is the highest level and cannot be upgraded further." << std::endl;
            return this;
        }
};

Tower* Tower::upgrade() {
    std::cout << "Upgrading Tower to Tower2" << std::endl;
    return new Tower2(position, level + 1, range + 10);
}

Tower* Tower2::upgrade() {
    std::cout << "Upgrading Tower2 to Tower3" << std::endl;
    return new Tower3(position, level + 1, range + 10);
}