#pragma once
#include <cmath>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "drawableObject.h"

/**
 * @brief Base class for all enemies
 * @implements sf::Drawable
 *
 * Contains basic attributes and methods for all enemies
 */
class Enemy : public DrawableObject
{
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    int hp;
    float speed;
    std::string enemy_type;
    int current_path_point = 0;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

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
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

    /**
     * @brief Animate enemy sprite
     * @param row Row corresponding to current enemy direction
     * @param deltaTime Time passed since last frame
     *
     * Update enemy sprite uvRect and change animation frame
     */
    void animate(int row, float deltaTime);

    /**
     * @brief Initialize enemy sprite
     *
     * Load enemy texture and set sprite attributes
     */
    virtual void initSprite() = 0;

protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::Texture texture;
    sf::Sprite sprite;
    Animation *animation;
    int animation_row;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Enemy object at position (0, 0)
     * @param enemy_type Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     *
     * Construct a new Enemy object with given type, hp and speed at position (0, 0)
     */
    Enemy(std::string enemy_type, int hp, float speed);

    /**
     * @brief Construct a new Enemy object at given position
     * @param enemy_type Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     * @param position Enemy start position
     *
     * Construct a new Enemy object with given type, hp, speed and start position
     */
    Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f position);

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

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set enemy start position
     * @param position Start position
     *
     * Set enemy start position to position given in sf::Vector2f format
     */
    void setStartPosition(sf::Vector2f position);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Check if enemy is dead
     * @return True if enemy is dead, false otherwise
     */
    bool isDead();

    /**
     * @brief Move enemy along path
     *
     * Moves enemy in the direction of the path
     */
    // sf::Vector2f moveAlong(std::vector<sf::Vector2f> &path);
    void moveAlong(std::vector<sf::Vector2f> &path);

    /**
     * @brief Deal damage to enemy
     * @param damage Amount of damage to deal
     *
     * Decrease enemy hp by damage amount and check if enemy is dead
     */
    void takeDamage(int damage);

    /**
     * @brief Update enemy position and animation
     * @param path Path for enemy to follow
     * @param deltaTime Time passed since last frame
     *
     * Update enemy position and animation based on path and time passed
     */
    void update(std::vector<sf::Vector2f> &path, float deltaTime);
};

//-----------------------------------
//              Peasant
//-----------------------------------

class Peasant : public Enemy
{
private:
    void initSprite() override;

public:
    Peasant();
    ~Peasant();
};

//-----------------------------------
//              Warrior
//-----------------------------------

class Warrior : public Enemy
{
private:
    void initSprite() override;

public:
    Warrior();
    ~Warrior();
};

//-----------------------------------
//            HeavyKnight
//-----------------------------------

class HeavyKnight : public Enemy
{
private:
    void initSprite() override;

public:
    HeavyKnight();
    ~HeavyKnight();
};
