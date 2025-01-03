#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "drawableObject.h"
#include "enemy.h"
#include "gun.h"
#include "logger.h"

// #ifndef ENEMY_H
// #define ENEMY_H
// #include "enemy.h"
// #endif

/**
 * @brief Base class for all towers
 * @implements sf::Drawable
 *
 * Contains basic attributes and methods for all towers, tower level 1
 */
class Tower : public DrawableObject {
private:
    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Draw tower on screen
     *
     * @param target Render target
     * @param states Render states
     *
     * Draws tower and range on screen with given render states.
     *
     * Implemented from sf::Drawable interface
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;


protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    int level;
    sf::Vector2f position;
    std::pair<int, int> occupiedTile;
    sf::Texture texture;
    sf::Sprite sprite;

    Gun* gun;
    int range;
    float shootTimer;

    sf::CircleShape rangeCircle;
    bool showRange;

    Logger* logger;

    //-----------------------------------
    //         Protected methods
    //-----------------------------------

    /**
     * @brief Initialize tower range
     *
     * Initialize tower range circle
     */
    void initRange();

    /**
     * @brief Initialize tower texture
     *
     * Load tower texture from file
     */
    virtual void initTexture();

    /**
     * @brief Initialize tower variables
     *
     * Load tower texture and set sprite position
     */
    void initVariables();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Default constructor
     */
    Tower();

    /**
     * @brief Construct a new Tower object at given position
     * @param position Tower position
     * @param level Tower level
     * @param range Tower range
     * @param gun Gun object
     *
     * Construct a new Tower object with given position, level, range and gun
     */
    // Tower(sf::Vector2f position, int level, int range, std::unique_ptr<Gun> gun);
    Tower(sf::Vector2f position, int level, int range, Gun* gun);

    /**
     * @brief Tower destructor
     *
     * Delete gun object
     */
    virtual ~Tower();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get tower gun
     * @return Gun object
     */
    Gun* getGun() const;

    /**
     * @brief Get tower level
     * @return Tower level
     */
    int getLevel() const;

    /**
     * @brief Get tower position
     * @return Tower position
     */
    sf::Vector2f getPosition() const override;

    /**
     * @brief Get tower range
     * @return Tower range
     */
    int getRange() const;

    /**
     * @brief Get range circle
     * @return Range circle object
     */
    sf::CircleShape* getRangeCircle();

    /**
     * @brief Get tile coordinates
     * @return Tile coordinates
     */
    std::pair<int, int> getTile();

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set tower position
     * @param pos New position
     */
    void setPosition(sf::Vector2f pos);

    /**
     * @brief Set tower range
     * @param range New range
     */
    void setRange(int range);

    /**
     * @brief Set tile coordinates
     * @param x X tile coordinate
     * @param y Y tile coordinate
     */
    void setTile(int x, int y);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Check if enemy is in range
     * @param enemy Enemy to check
     * @return True if enemy is in range, false otherwise
     *
     * Check if enemy is in tower range
     */
    bool enemyInRange(Enemy* enemy);

    /**
     * @brief Get closest enemy
     * @return Closest enemy
     *
     * Calculate distances to enemies and get enemy to shoot at
     */
    Enemy* getClosestEnemy(const std::vector<Enemy*>& enemies);

    /**
     * @brief Place tower on map
     * @param x X coordinate
     * @param y Y coordinate
     *
     * Place tower on map at given coordinates
     */
    void placeTower(std::pair<int, int> tilePosition);

    /**
     * @brief Remove tower from map
     *
     * Remove tower from map
     */
    void removeTower();

    /**
     * @brief Shoot at enemy
     * @param enemy Enemy to shoot at
     *
     * Shoot at enemy if tower is placed and enemy is in range
     */
    virtual void shoot(Enemy* enemy, float deltaTime);

    /**
     * @brief Show tower range
     */
    void showTowerRange();

    /**
     * @brief Hide tower range
     */
    void hideTowerRange();

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 2
     */
    virtual Tower* upgrade();
};

//-----------------------------------
//              Tower2
//-----------------------------------

/**
 * @brief Tower level 2
 * @extends Tower
 *
 * Contains attributes and methods for tower level 2
 */
class Tower2 : public Tower {
public:
    Tower2(sf::Vector2f position, int level, int range, Gun* gun);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 3
     */
    Tower* upgrade() override;

    void initTexture() override;
};

//-----------------------------------
//              Tower3
//-----------------------------------

/**
 * @brief Tower level 3
 * @extends Tower
 *
 * Contains attributes and methods for tower level 3
 */
class Tower3 : public Tower {
public:
    Tower3(sf::Vector2f position, int level, int range, Gun* gun);

    /**
     * @brief Upgrade tower
     * @return Self
     *
     * @attention Tower3 is the highest level tower and cannot be upgraded
     */
    Tower* upgrade() override;

    void initTexture() override;
};