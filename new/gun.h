#include <iostream>
#include <string>

class Gun
{
protected:
    int damage;
    float shooting_speed;
    std::string gun_name;

public:
    Gun(std::string gun_name, int damage, float shooting_speed);

    virtual ~Gun();

    virtual void fire();

    std::string getType();

    int getDamage();
};

class MachineGun : public Gun
{
public:
    MachineGun();

    void fire() override;
};

class HighDamageGun : public Gun
{
public:
    HighDamageGun();

    void fire() override;
};

class SniperRifle : public Gun
{
public:
    SniperRifle();

    void fire() override;
};