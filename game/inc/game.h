#pragma once

#include <vector>

#include "enemy.h"
#include "levelInfo.h"
#include "logger.h"
#include "menu.h"
#include "selectBox.h"
#include "tower.h"
#include "ui.h"
#include "windowHandler.h"

class Game {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    WindowHandler* window;
    SelectBox* selectBox;
    UI* ui;

    LevelInfo* levelInfo;
    int level;
    int round;
    int playerHp;
    int money;

    sf::Sprite background;
    sf::Texture backgroundTexture;

    std::vector<Enemy*> enemies;
    std::vector<sf::Vector2f> enemyPath;
    float spawnDelay;

    std::vector<Tower*> towers;
    std::pair<int, int> currentTile;
    bool canPlaceTower;
    int gunType;
    bool newTowerChosen;

    bool cursorOnMap;
    bool isRoundStarted;
    bool endGame;

    sf::Clock clock;
    float deltaTime;
    float spawnTimer;

    Logger* logger;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

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
     * @brief Load level from map file
     * @param level Level number
     *
     * Loads level information from `levels` directory.
     *
     * `level_X.map` file contains enemy path, enemy types and allowed tower positions
     */
    void loadLevel(int level);

    /**
     * @brief Load game state from file
     *
     * Load game state from `autosave.txt` file
     */
    void loadSave();

    /**
     * @brief Get cursor position relative to map
     * @return Cursor position on map
     *
     * Converts screen coordinates to map coordinates and calculates tile position
     */
    sf::Vector2f getCursorProjection();

    /**
     * @brief Check if cursor is on map
     * @return True if cursor is on map, false otherwise
     *
     * Checks if cursor is inside the map polygon
     */
    bool isCursorOnMap();

    /**
     * @brief Game loop
     *
     * Calls `update` and `render` functions in a loop while game is running
     */
    void gameLoop();

    /**
     * @brief Handle UI input
     *
     * Handle button clicks on UI
     */
    void interpretUIInput();

    /**
     * @brief Check if round is over
     *
     * Check if all enemies are dead and no new enemies are to be spawned
     */
    void isRoundOver();

    /**
     * @brief Tower attack
     *
     * Check if tower is placed and enemy is in range, then shoot at enemy
     */
    void attack();

    /**
     * @brief Place new tower on map
     *
     * If cursor is on map and left mouse button is pressed, place new tower on map
     */
    void placeTower();

    /**
     * @brief Sell tower
     *
     * Remove tower from map and return money to player
     */
    void sellTower();

    /**
     * @brief Add enemy to the game
     * @param enemyType Character representing enemy type
     *
     *  Used in loadLevel function to add enemies to the game by their shortened name
     * (P - Peasant, W - Warrior, H - HeavyKnight)
     */
    void addEnemy(char enemyType);

    /**
     * @brief Spawn next enemy
     *
     * Spawns next enemy from `levelInfo` and adds it to `enemies` vector
     */
    void spawnEnemy();

    /**
     * @brief Update window
     *
     * Calls `WindowHandler::update` function
     */
    void update();

    /**
     * @brief Update games clock
     *
     * Updates games clock every iteration of game loop
     */
    void updateClock();

    /**
     * @brief Update enemies
     *
     * Move enemies along path, check if they are dead or
     * reached the end of the path
     */
    void updateEnemies();

    /**
     * @brief Update towers
     *
     * Place new tower on map, sell tower, upgrade tower
     */
    void updateTowers();

    /**
     * @brief Updates position of selectBox
     *
     * If hovering over a map, change position of selectBox accordingly
     */
    void updateSelectBox();

    /**
     * @brief Update UI
     *
     * Update round, health and money text on screen
     */
    void updateUI();

    /**
     * @brief Render all objects
     *
     * Calls `WindowHandler::render` passing background and all objects to render
     */
    void render();

    /**
     * @brief End game screen
     *
     * Display end game screen
     */
    void endingScreen();

    /**
     * @brief Autosave game
     *
     * Save game state to `autosave.txt` file at exit
     */
    void autosave();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Game object
     *
     * Initializes game variables
     */
    Game();

    /**
     * @brief Destroy the Game object
     *
     * Deletes window object and clears enemies and towers vectors
     */
    ~Game();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get time passed since last frame
     * @return Delta time
     */
    float getDeltaTime();

    /**
     * @brief Get level number
     * @return Level number
     */
    int getLevel() const;

    /**
     * @brief Get round number
     * @return Round number
     */
    int getRound() const;

    /**
     * @brief Get player money
     * @return Player money
     */
    int getMoney() const;

    /**
     * @brief Get player HP
     * @return Player HP
     */
    int getPlayerHp() const;

    /**
     * @brief Get enemies vector
     * @return Enemies vector
     */
    std::vector<Enemy*> getEnemies() const;

    /**
     * @brief Get towers vector
     * @return Towers vector
     */
    std::vector<Tower*> getTowers() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Overloaded operator<<
     * @param os Output stream
     * @param game Game object
     * @return Output stream
     *
     * Overloaded operator<< to print game state to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

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