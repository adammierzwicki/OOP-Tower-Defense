#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>

/**
 * @brief Class for loading and storing level information
 *
 * Contains methods for loading level information from file and accessors for level data
 */
class LevelInfo
{
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    int level;
    std::string mapFilePath;
    std::fstream mapFile;
    std::map<std::string, int> enemies;
    std::vector<sf::Vector2f> path;
    std::pair<int, int> mapSize;
    std::vector<std::vector<bool>> map;
    sf::Vector2f mapTileSize;
    sf::Vector2f mapCorners[4];
    sf::Texture levelBackground;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Load map corner coordinates
     *
     * Reads map corner coordinates and tile size from map file
     */
    void loadCoordinates();

    /**
     * @brief Load enemies from map file
     *
     * Reads enemy types and their number from map file
     */
    void loadEnemies();

    /**
     * @brief Load level from map file
     *
     * Load level information from map file
     */
    void loadLevel();

    /**
     * @brief Load blocked tiles from map file
     *
     * Reads map size and blocked tiles from map file
     */
    void loadMap();

    /**
     * @brief Load path points from map file
     *
     * Reads path points from map file
     */
    void loadPathPoints();

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
     *
     * Get level background texture
     */
    sf::Texture getBackgroundTexture();

    /**
     * @brief Get enemies
     * @return Enemies
     *
     * Get enemies in map format
     */
    std::map<std::string, int> getEnemies();

    /**
     * @brief Get map corners coordinates
     * @return Vector with map corners coordinates
     */
    sf::Vector2f *getMapCorners();

    /**
     * @brief Get map width
     * @return Map width
     */
    int getMapWidth();

    /**
     * @brief Get map height
     * @return Map height
     */
    int getMapHeight();

    /**
     * @brief Get map tile size
     * @return Map tile size
     */
    sf::Vector2f getMapTileSize();

    /**
     * @brief Get path points
     * @return Path points
     *
     * Get path points in vector format
     */
    std::vector<sf::Vector2f> getPath();

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Check if tile is blocked
     * @param x X tile coordinate
     * @param y Y tile coordinate
     * @return True if tile is blocked, false otherwise
     *
     * Get map size in pair format
     */
    bool isTileBlocked(int x, int y);

    /**
     * @brief Mark tile as blocked
     * @param x X tile coordinate
     * @param y Y tile coordinate
     * 
     * Mark tile as blocked in map
     */
    void blockTile(int x, int y);

    /**
     * @brief Print debug level information
     *
     * Prints info about level loaded from map file
     */
    void printInfo();

    /**
     * @brief Remove tower from map
     * @param x X tile coordinate
     * @param y Y tile coordinate
     *
     * Mark tile as unblocked in map
     */
    void unblockTile(int x, int y);
};