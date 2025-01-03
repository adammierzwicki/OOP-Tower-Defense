#include "../inc/gun.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Gun::Gun(std::string gun_name, int damage, float shooting_speed) : gun_name(gun_name), damage(damage), shooting_speed(shooting_speed) {
    this->logger = Logger::getInstance();
}

Gun::Gun(Gun const& gun) : gun_name(gun.gun_name), damage(gun.damage), shooting_speed(gun.shooting_speed) {
    this->logger = Logger::getInstance();
}

Gun::~Gun() {}


//-----------------------------------
//             Accessors
//-----------------------------------

int Gun::getDamage() const { return damage; }

float Gun::getDelay() const { return shooting_speed; }

std::string Gun::getName() const { return gun_name; }

char Gun::getType() const { return gun_name[0]; }

//-----------------------------------
//          Public methods
//-----------------------------------

void Gun::fire() {
    //! add projectile animation
    this->logger->log(LogLevel::DEBUG, "Shooting from " + gun_name + " with damage " + std::to_string(damage) + " and speed " + std::to_string(shooting_speed), "Gun::fire()", __LINE__);
}

//-----------------------------------
//             Machine Gun
//-----------------------------------

MachineGun::MachineGun() : Gun("machine_gun", 20, 0.5) {}

void MachineGun::fire() {
    this->logger->log(LogLevel::DEBUG, "Shooting from " + gun_name + " with damage " + std::to_string(damage) + " and speed " + std::to_string(shooting_speed), "MachineGun::fire()", __LINE__);
}

//-----------------------------------
//           High Damage Gun
//-----------------------------------

HighDamageGun::HighDamageGun() : Gun("high_damage_gun", 100, 1.0) {}

void HighDamageGun::fire() {
    this->logger->log(LogLevel::DEBUG, "Shooting from " + gun_name + " with damage " + std::to_string(damage) + " and speed " + std::to_string(shooting_speed), "HighDamageGun::fire()", __LINE__);
}

//-----------------------------------
//           Sniper Rifle
//-----------------------------------

SniperRifle::SniperRifle() : Gun("sniper_rifle", 200, 5.0) {}

void SniperRifle::fire() {
    this->logger->log(LogLevel::DEBUG, "Shooting from " + gun_name + " with damage " + std::to_string(damage) + " and speed " + std::to_string(shooting_speed), "SniperRifle::fire()", __LINE__);
}