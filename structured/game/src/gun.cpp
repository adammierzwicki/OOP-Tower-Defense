#include "../inc/gun.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Gun::Gun(std::string gun_name, int damage, float shooting_speed)
    : gun_name(gun_name), damage(damage), shooting_speed(shooting_speed) {}

Gun::~Gun() {}

//-----------------------------------
//             Accessors
//-----------------------------------

std::string Gun::getType() { return gun_name; }

int Gun::getDamage() { return damage; }

float Gun::getDelay() { return shooting_speed; }

//-----------------------------------
//          Public methods
//-----------------------------------

void Gun::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}

//-----------------------------------
//             Machine Gun
//-----------------------------------

MachineGun::MachineGun() : Gun("machine_gun", 20, 0.5) {}

void MachineGun::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}

//-----------------------------------
//           High Damage Gun
//-----------------------------------

HighDamageGun::HighDamageGun() : Gun("high_damage_gun", 100, 1.0) {}

void HighDamageGun::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}

//-----------------------------------
//           Sniper Rifle
//-----------------------------------

SniperRifle::SniperRifle() : Gun("sniper_rifle", 200, 5.0) {}

void SniperRifle::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}