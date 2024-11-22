#include <iostream>
#include <memory>
#include "gun.cpp"


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

        void place_tower(int x, int y) {
            if (is_placed) {
                std::cout << "Tower is already placed at (" << position.first << ", " << position.second << ")." << std::endl;
                return;
            }
            position = std::make_pair(x, y);
            is_placed = true;
            std::cout << "Tower placed at (" << x << ", " << y << ")." << std::endl;
        }

        void remove_tower() {
            if (!is_placed) {
                std::cout << "Tower is not placed." << std::endl;
                return;
            }
            std::cout << "Tower removed from (" << position.first << ", " << position.second << ")." << std::endl;
            is_placed = false;
            position = std::make_pair(-1, -1);
        }

        std::pair<int, int> get_position() {
            return position;
        }

        virtual void shoot() {
            if (!is_placed) {
                std::cout << "Tower is not placed and cannot shoot." << std::endl;
                return;
            }
            gun_type->fire();
        }

        virtual Tower* upgrade(); // here I only declare this funciton, because the compiler will not see Tower 2 yet
};

class Tower2 : public Tower {
    public:
        Tower2(std::pair<int, int> position = std::make_pair(-1, -1), int level = 2, int range = 15)
            : Tower(position, level, range, std::make_unique<HighDamageGun>()) {
            std::cout << "Tower2 initialized with High Damage Gun." << std::endl;
        }

        Tower* upgrade() override;
};

class Tower3 : public Tower {
    public:
        Tower3(std::pair<int, int> position = std::make_pair(-1, -1), int level = 3, int range = 25)
            : Tower(position, level, range, std::make_unique<SniperRifle>()) {
            std::cout << "Tower3 initialized with Sniper Rifle." << std::endl;
        }

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

int main() {
    Tower* tower = new Tower();
    tower->place_tower(1, 2);
    tower->shoot();

    Tower* upgradedTower = tower->upgrade();
    delete tower;
    upgradedTower->shoot();

    Tower* finalTower = upgradedTower->upgrade();
    delete upgradedTower;
    finalTower->shoot();

    Tower* maxTower = finalTower->upgrade();
    delete maxTower;

    return 0;
}