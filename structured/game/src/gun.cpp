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

MachineGun::MachineGun() : Gun("Machine Gun", 20, 3.0) {}

void MachineGun::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}

//-----------------------------------
//           High Damage Gun
//-----------------------------------

HighDamageGun::HighDamageGun() : Gun("High Damage Gun", 100, 1.0) {}

void HighDamageGun::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}

//-----------------------------------
//           Sniper Rifle
//-----------------------------------

SniperRifle::SniperRifle() : Gun("Sniper Rifle", 200, 5.0) {}

void SniperRifle::fire()
{
    std::cout << "Shooting from " << gun_name << " with damage " << damage << " and speed " << shooting_speed << std::endl;
}