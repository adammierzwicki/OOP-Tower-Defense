#include <iostream>
#include <string>

class Gun {
    protected:
        int damage;
        float shooting_speed;
        std::string gun_name;

    public:
        Gun(std::string gun_name, int damage, float shooting_speed)
            : gun_name(gun_name), damage(damage), shooting_speed(shooting_speed) {}

        virtual ~Gun() {}

        virtual void fire() {
            std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;

        }

        std::string getType() { return gun_name; }
};

class MachineGun : public Gun {
    public:
        MachineGun() : Gun("Machine Gun", 20, 3.0) {}

        void fire() override {
            std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
        }
};

class HighDamageGun : public Gun {
    public:
        HighDamageGun() : Gun("High Damage Gun", 100, 1.0) {}

        void fire() override {
            std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
        }
};


class SniperRifle : public Gun {
    public:
        SniperRifle() : Gun("Sniper Rifle", 160, 0.8) {}

        void fire() override {
            std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
        }
};