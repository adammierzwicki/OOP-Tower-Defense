#include <vector>

#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H
#include "windowHandler.h"
#endif

#ifndef ENEMY_H
#define ENEMY_H
#include "enemy.h"
#endif

#ifndef TOWER_H
#define TOWER_H
#include "tower.h"
#endif

#ifndef LEVELINFO_H
#define LEVELINFO_H
#include "levelInfo.h"
#endif

#ifndef SELECTBOX_H
#define SELECTBOX_H
#include "selectBox.h"
#endif

#ifndef MENU_H
#define MENU_H
#include "menu.h"
#endif

class Game
{
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    WindowHandler *window;
    std::vector<Enemy *> enemies;
    std::vector<Tower *> towers;
    int level;
    LevelInfo *levelInfo;
    int playerHp;
    int money;
    bool endGame;
    std::vector<sf::Vector2f> enemyPath;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    SelectBox *selectBox;
    bool cursorOnMap;
    bool canPlaceTower;

    std::pair<int, int> currentTile;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Add enemy to the game
     * @param enemyType Character representing enemy type
     *
     *  Used in loadLevel function to add enemies to the game by their shortened name
     * (P - Peasant, W - Warrior, H - HeavyKnight)
     */
    void addEnemy(char enemyType);

    /**
     * @brief Game loop
     *
     * Calls `update` and `render` functions in a loop while game is running
     */
    void gameLoop();

    /**
     * @brief Get cursor position relative to map
     * @return Cursor position on map
     *
     * Converts screen coordinates to map coordinates and calculates tile position
     */
    sf::Vector2f getCursorProjection();

    /**
     * @brief Initialize game variables
     *
     * Creates new WindowHandler object and initializes default starting values:
     * level = 1, endGame = false, playerHp = 100, money = 100
     */
    void initVariables();

    /**
     * @brief Load map image
     *
     * Loads map image from `textures` directory and sets it as background
     */
    void initWorld();

    /**
     * @brief Check if cursor is on map
     * @return True if cursor is on map, false otherwise
     *
     * Checks if cursor is inside the map polygon
     */
    bool isCursorOnMap();

    /**
     * @brief Load level from map file
     * @param level Level number
     *
     * Loads level information from `levels` directory.
     *
     * `level_X.map` file contains enemy path, enemy types and allowed tower positions
     */
    void loadLevel(int level);

    /**
     * @brief Place new tower on map
     *
     * If cursor is on map and left mouse button is pressed, place new tower on map
     */
    void placeTower();

    /**
     * @brief Render all objects
     *
     * Calls `WindowHandler::render` passing background and all objects to render
     */
    void render();

    /**
     * @brief Update window
     *
     * Calls `WindowHandler::update` function
     */
    void update();

    /**
     * @brief Sell tower
     *
     * Remove tower from map and return money to player
     */
    void sellTower();
    
    /**
     * @brief Updates position of selectBox
     *
     * If hovering over a map, change position of selectBox accordingly
     */
    void updateSelectBox();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Game object
     *
     * Initializes game variables and loads level 1
     */
    Game();

    /**
     * @brief Destroy the Game object
     *
     * Deletes window object and clears enemies and towers vectors
     */
    ~Game();

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Start game loop
     *
     * Opens start menu and starts game loop
     */
    void startGame();

    /**
     * @brief Start menu
     *
     * Opens start menu and waits for user to start a game, open settings or exit the game
     */
    void startingScreen();
};