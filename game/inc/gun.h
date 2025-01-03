#pragma once

#include <iostream>
#include <string>

#include "../inc/logger.h"

/**
 * @brief Abstract class for all guns
 *
 * Contains basic attributes and methods for all guns
 */
class Gun {
protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    std::string gun_name;
    int damage;
    float shooting_speed;

    Logger* logger;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Gun object
     * @param gun_name Gun type name
     * @param damage Gun damage
     * @param shooting_speed Gun shooting speed
     *
     * Construct a new Gun object with given attributes
     */
    Gun(std::string gun_name, int damage, float shooting_speed);

    /**
     * @brief Copy Gun object
     * @param gun Gun object
     *
     * Cerate copy of Gun object from another Gun object
     */
    Gun(Gun const& gun);

    /**
     * @brief Default destructor
     */
    virtual ~Gun();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get gun damage
     * @return Gun damage
     */
    int getDamage() const;

    /**
     * @brief Get gun delay
     * @return Gun delay
     */
    float getDelay() const;

    /**
     * @brief Get gun full name
     * @return Gun name
     */
    std::string getName() const;

    /**
     * @brief Get gun type (first letter of name)
     * @return Gun type
     */
    char getType() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Fire gun
     *
     * Fire gun and print message
     */
    virtual void fire();
};

/**
 * @brief Machine gun class
 *
 * Contains attributes and methods for machine gun
 */
class MachineGun : public Gun {
public:
    MachineGun();

    void fire() override;
};

/**
 * @brief High damage gun class
 *
 * Contains attributes and methods for high damage gun
 */
class HighDamageGun : public Gun {
public:
    HighDamageGun();

    void fire() override;
};

/**
 * @brief Sniper rifle class
 *
 * Contains attributes and methods for sniper rifle
 */
class SniperRifle : public Gun {
public:
    SniperRifle();

    void fire() override;
};