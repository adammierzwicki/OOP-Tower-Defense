#pragma once

#include <fstream>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "customQueue.h"
#include "logger.h"

/**
 * @brief Class for loading and storing level information
 *
 * Contains methods for loading level information from file and accessors for level data
 */
class LevelInfo {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    int level;
    std::ifstream mapFile;
    sf::Texture levelBackground;

    std::map<int, Queue<char>> rounds;
    int roundsCount;

    std::vector<sf::Vector2f> path;
    int pathLength;

    std::pair<int, int> mapSize;
    std::vector<std::vector<bool>> map;
    sf::Vector2f mapTileSize;
    sf::Vector2f mapCorners[4];

    Logger* logger;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Load level from map file
     *
     * Load level information from map file
     */
    void loadLevel();

    /**
     * @brief Load path points from map file
     *
     * Reads path points from map file
     */
    void loadPathPoints();

    /**
     * @brief Load enemies from map file
     *
     * Reads enemy types and their number from map file
     */
    void loadEnemies();

    /**
     * @brief Load blocked tiles from map file
     *
     * Reads map size and blocked tiles from map file
     */
    void loadMap();

    /**
     * @brief Load map corner coordinates
     *
     * Reads map corner coordinates and tile size from map file
     */
    void loadCoordinates();

    /**
     * @brief Load level background texture
     *
     * Load level background texture from file
     */
    void loadTexture();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Level Info object
     * @param level Level number
     *
     * Initializes level, loads data from map file and loads background texture
     */
    LevelInfo(int level);

    /**
     * @brief Destroy the Level Info object
     *
     * Closes map file if open. Destroys LevelInfo object
     */
    ~LevelInfo();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get level background texture
     * @return Level background texture
     */
    sf::Texture getBackgroundTexture() const;

    /**
     * @brief Get map corners coordinates
     * @return Vector with map corners coordinates
     */
    const sf::Vector2f* getMapCorners() const;

    /**
    * @brief Get map height
    * @return Map height
    */
    int getMapHeight() const;

    /**
     * @brief Get map width
     * @return Map width
     */
    int getMapWidth() const;

    /**
     * @brief Get map tile size
     * @return Map tile size
     */
    sf::Vector2f getMapTileSize() const;

    /**
     * @brief Get enemies vector
     * @param round Round number
     * @return Enemies vector
     */
    char getNextEnemy(int round);

    /**
     * @brief Get path points
     * @return Path points
     */
    std::vector<sf::Vector2f> getPath() const;

    /**
     * @brief Get last point of path
     * @return End point of path
     */
    sf::Vector2f getLastPathPoint() const;

    /**
     * @brief Get number of path points
     * @return Path length
     */
    int getPathLength() const;

    /**
     * @brief Get number of rounds
     * @return Number of rounds
     */
    int getRoundsCount() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Check if tile is blocked
     * @param tile Pair of tile coordinates
     * @return True if tile is blocked, false otherwise
     */
    bool isTileBlocked(std::pair<int, int> tile) const;

    /**
     * @brief Mark tile as blocked
     * @param tile Pair of tile coordinates
     *
     * Mark tile as blocked in map
     */
    void blockTile(std::pair<int, int> tile);
    /**
     * @brief Remove tower from map
     * @param tile Pair of tile coordinates
     *
     * Mark tile as unblocked in map
     */
    void unblockTile(std::pair<int, int> tile);

    /**
     * @brief Check if there are enemies left in round
     * @param round Round number
     * @return True if there are enemies left, false otherwise
     */
    bool hasNextEnemy(int round) const;
};