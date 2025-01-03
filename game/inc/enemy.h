#pragma once

#include <cmath>
#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include "../inc/animation.h"
#include "../inc/drawableObject.h"
#include "../inc/logger.h"

/**
 * @brief Base class for all enemies
 * @implements sf::Drawable
 *
 * Contains basic attributes and methods for all enemies
 */
class Enemy : public DrawableObject {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    std::string enemyType;
    int hp;
    float speed;
    int value;
    int damage;
    unsigned int currentPathPoint;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Animate enemy sprite
     * @param deltaTime Time passed since last frame
     *
     * Update enemy sprite uvRect and change animation frame
     */
    void animate(float deltaTime);

    /**
     * @brief Draw enemy on screen
     *
     * @param target Render target
     * @param states Render states
     *
     * Draws enemy sprite on screen with given render states.
     *
     * Implemented from sf::Drawable interface
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

    /**
     * @brief Initialize enemy sprite
     *
     * Load enemy texture and set sprite attributes
     */
    virtual void initSprite() = 0;

    /**
     * @brief Initialize enemy variables
     *
     * Set default values for enemy attributes
     */
    void initVariables();

protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::Sprite sprite;
    sf::Texture texture;
    Animation* animation;
    unsigned int animationRow;

    Logger* logger;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Enemy object at position (0, 0)
     * @param enemyType Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     * @param value Enemy value
     * @param damage Damage dealt by enemy
     *
     * Construct a new Enemy object with given type, hp and speed at position (0, 0)
     */
    Enemy(std::string enemyType, int hp, float speed, int value, int damage);

    /**
     * @brief Construct a new Enemy object at given position
     * @param enemyType Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     * @param value Enemy value
     * @param damage Damage dealt by enemy
     * @param position Enemy start position
     *
     * Construct a new Enemy object with given type, hp, speed and start position
     */
    Enemy(std::string enemyType, int hp, float speed, int value, int damage, sf::Vector2f position);

    /**
     * @brief Destroy the Enemy object
     *
     * Default destructor for Enemy object
     */
    ~Enemy();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get damage dealt by enemy
     * @return Damage dealt
     */
    int getDamage() const;

    /**
     * @brief Get enemy hp
     * @return Enemy hp
     */
    int getHp() const;

    /**
     * @brief Get current enemy position
     * @return Enemy position
     */
    sf::Vector2f getPosition() const override;

    /**
     * @brief Get enemy movement speed
     * @return Enemy speed
     */
    int getSpeed() const;

    /**
     * @brief Get enemy type
     * @return Enemy type
     */
    std::string getType() const;

    /**
     * @brief Get enemy value
     * @return Enemy value
     */
    int getValue() const;

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set enemy start position
     * @param position Start position
     */
    void setStartPosition(sf::Vector2f position);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Update enemy position and animation
     * @param path Path for enemy to follow
     * @param deltaTime Time passed since last frame
     *
     * Update enemy position and animation based on path and time passed
     */
    void update(std::vector<sf::Vector2f>& path, float deltaTime);

    /**
     * @brief Move enemy along path
     * @param path Path for enemy to follow
     *
     * Moves enemy in the direction of the path
     */
    void moveAlong(std::vector<sf::Vector2f>& path);

    /**
     * @brief Deal damage to enemy
     * @param damage Amount of damage to deal
     *
     * Decrease enemy hp by damage amount and check if enemy is dead
     */
    void takeDamage(int damage);

    /**
     * @brief Check if enemy is dead
     * @return True if enemy is dead, false otherwise
     */
    bool isDead();
};

//-----------------------------------
//              Peasant
//-----------------------------------

class Peasant : public Enemy {
private:
    void initSprite() override;

public:
    Peasant();
    Peasant(bool loadTexture = false);
    ~Peasant();
};

//-----------------------------------
//              Warrior
//-----------------------------------

class Warrior : public Enemy {
private:
    void initSprite() override;

public:
    Warrior();
    ~Warrior();
};

//-----------------------------------
//            HeavyKnight
//-----------------------------------

class HeavyKnight : public Enemy {
private:
    void initSprite() override;

public:
    HeavyKnight();
    ~HeavyKnight();
};