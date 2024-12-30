#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "gun.h"
#include "drawableObject.h"
#include "enemy.h"
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
class Tower : public DrawableObject
{
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
     * Draws tower sprite on screen with given render states.
     *
     * Implemented from sf::Drawable interface
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
    
    
protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::Vector2f position;
    std::pair<int, int> occupiedTile;
    int level;
    int range;
    Gun *gun;
    sf::Texture texture;
    sf::Sprite sprite;

    float shootTimer;
    sf::CircleShape rangeCircle;
    bool showRange;


    void initRange();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Default constructor for Tower object
     *
     * Default Tower constructor
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
    Tower(sf::Vector2f position, int level, int range, Gun *gun);

    /**
     * @brief Destroy the Tower object
     *
     * Default destructor for Tower object
     */
    virtual ~Tower();

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Get tower range
     * @return Tower range
     *
     * Calculate distances to enemies and get enemy to shoot at
     */
    Enemy *getClosestEnemy(const std::vector<Enemy *> &enemies);

    /**
     * @brief Get tower position
     * @return Tower position
     *
     * Get tower position in sf::Vector2f format
     */
    sf::Vector2f getPosition() const override;

    /**
     * @brief Initialize tower variables
     *
     * Load tower texture and set sprite position
     */
    void initVariables();

    virtual void initTexture();

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
     * @brief Set tile coordinates
     * @param x X tile coordinate
     * @param y Y tile coordinate
     *
     * Set tower coordinates relative to map
     */
    void setTile(int x, int y);

    /**
     * @brief Get tile coordinates
     * @return Tile coordinates
     *
     * Get tower coordinates relative to map
     */
    std::pair<int, int> getTile();

    /**
     * @brief Shoot at enemy
     * @param enemy Enemy to shoot at
     *
     * Shoot at enemy if tower is placed and enemy is in range
     */
    virtual void shoot(Enemy *enemy, float deltaTime);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 2
     */
    virtual Tower *upgrade();

    void showTowerRange();

    void hideTowerRange();

    bool enemyInRange(Enemy *enemy);

    int getLevel() const;

    Gun *getGun() const;

    int getRange() const;

    void setPosition(sf::Vector2f pos);

    void setRange(int range);

    sf::CircleShape *getRangeCircle();
};

/**
 * @brief Tower level 2
 * @extends Tower
 *
 * Contains attributes and methods for tower level 2
 */
class Tower2 : public Tower
{
public:
    Tower2(sf::Vector2f position, int level, int range, Gun *gun);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 3
     */
    Tower *upgrade() override;

    void initTexture() override;
};

/**
 * @brief Tower level 3
 * @extends Tower
 *
 * Contains attributes and methods for tower level 3
 */
class Tower3 : public Tower
{
public:
    Tower3(sf::Vector2f position, int level, int range, Gun *gun);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * @attention Tower3 is the highest level tower and cannot be upgraded
     */
    Tower *upgrade() override;

    void initTexture() override;
};
