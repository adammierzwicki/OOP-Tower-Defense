#pragma once
#include <iostream>
#include <string>

/**
 * @brief Abstract class for all guns
 *
 * Contains basic attributes and methods for all guns
 */
class Gun
{
protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    std::string gun_name;
    int damage;
    float shooting_speed;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    Gun(std::string gun_name, int damage, float shooting_speed);

    virtual ~Gun();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get gun type
     * @return Gun type name
     *
     * Get gun type name
     */
    std::string getType();

    /**
     * @brief Get gun damage
     * @return Gun damage
     *
     * Get gun damage
     */
    int getDamage();
        
    /**
     * @brief Get gun delay
     * @return Gun delay
     *
     * Get gun delay
     */
    float getDelay();

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
class MachineGun : public Gun
{
public:
    MachineGun();

    void fire() override;
};

/**
 * @brief High damage gun class
 *
 * Contains attributes and methods for high damage gun
 */
class HighDamageGun : public Gun
{
public:
    HighDamageGun();

    void fire() override;
};

/**
 * @brief Sniper rifle class
 *
 * Contains attributes and methods for sniper rifle
 */
class SniperRifle : public Gun
{
public:
    SniperRifle();

    void fire() override;
};