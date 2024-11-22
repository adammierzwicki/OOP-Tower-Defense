#include <iostream>
#include <utility>
#include <cmath>

class Enemy {
    private:
        int hp;
        int speed;
        std::pair<int, int> position; // assume position is (x, y) coordinates
        std::string enemy_type;
    
    public:
        Enemy(std::string enemy_type, int hp, int speed) {
            this->enemy_type = enemy_type;
            this->hp = hp;
            this->speed = speed;
        }

        ~Enemy() {
            std::cout << "Enemy destroyed" << std::endl;
        }

        int getHp() {
            return hp;
        }

        int getSpeed() {
            return speed;
        }

        std::pair<int, int> getPosition() {
            return position;
        }

        void setStartPosition(std::pair<int, int> position) {
            this->position = position;
        }

        void move() {
            position.first += speed;
            position.second += speed;
            std::cout << "Enemy moves with speed " << speed << std::endl;
            std::cout << "Enemy position: " << position.first << " " << position.second << std::endl;
        }

        void takeDamage(int damage) {
            hp -= damage;
            if (isDead()) {
                std::cout << "Enemy died" << std::endl;
                //todo: remove from screen and queue
            }
            else {
                std::cout << "Enemy takes " << damage << " damage" << std::endl;
            }
        }

        bool isDead() {
            return hp <= 0;
        }

        //todo: someType animate();
        //todo: someType drawOnScreen();
};

class Peasant : public Enemy {
    private:
        // image = ["enemy1_1.png", enemy1_2.png]; vector of poses

    public:
        Peasant() : Enemy("Peasant", 100, 2) {
            std::cout << "Peasant created" << std::endl;
        }

        ~Peasant() {
            std::cout << "Peasant destroyed" << std::endl;
        }
};

class Warrior : public Enemy {
    private:
        // image = "enemy2.png";
    public:
        Warrior() : Enemy("Warrior", 200, 5) {
            std::cout << "Warrior created" << std::endl;
        }

        ~Warrior() {
            std::cout << "Warrior destroyed" << std::endl;
        }
};

class HeavyKnight : public Enemy {
    private:
        // image = "enemy3.png";
    public:
        HeavyKnight() : Enemy("HeavyKnight", 600, 1) {
            std::cout << "HeavyKnight created" << std::endl;
        }

        ~HeavyKnight() {
            std::cout << "HeavyKnight destroyed" << std::endl;
        }
};
