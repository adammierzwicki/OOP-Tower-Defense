#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "gun.h"

#ifndef ENEMY_H
#define ENEMY_H
#include "enemy.h"
#endif

/**
 * @brief Base class for all towers
 * @implements sf::Drawable
 *
 * Contains basic attributes and methods for all towers, tower level 1
 */
class Tower : public sf::Drawable
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
    bool is_placed;
    int level;
    int range;
    // todo: why unique_ptr?  std::unique_ptr<Gun> gun_type;
    Gun *gun_type;
    sf::Texture texture;
    sf::Sprite sprite;

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
    sf::Vector2f getPosition();

    /**
     * @brief Initialize tower variables
     *
     * Load tower texture and set sprite position
     */
    void initVariables();

    /**
     * @brief Place tower on map
     * @param x X coordinate
     * @param y Y coordinate
     *
     * Place tower on map at given coordinates
     */
    void placeTower(int x, int y);

    /**
     * @brief Remove tower from map
     *
     * Remove tower from map
     */
    void removeTower();

    /**
     * @brief Set tile
     * @param x X tile coordinate
     * @param y Y tile coordinate
     *
     * Set tile coordinates for tower
     */
    void setTile(int x, int y);

    std::pair<int, int> getTile();

    /**
     * @brief Shoot at enemy
     * @param enemy Enemy to shoot at
     *
     * Shoot at enemy if tower is placed and enemy is in range
     */
    virtual void shoot(Enemy *enemy = nullptr);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 2
     */
    virtual Tower *upgrade();
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
    Tower2(sf::Vector2f position, int level, int range);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * Upgrade tower to level 3
     */
    Tower *upgrade() override;
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
    Tower3(sf::Vector2f position, int level, int range);

    /**
     * @brief Upgrade tower
     * @return Upgraded tower
     *
     * @attention Tower3 is the highest level tower and cannot be upgraded
     */
    Tower *upgrade() override;
};
