#include "windowHandler.h"
#include <vector>

#ifndef ENEMY_H
#define ENEMY_H
#include "enemy.h"
#endif

#ifndef TOWER_H
#define TOWER_H
#include "tower.h"
#endif

#ifndef MENU_H
#define MENU_H
#include "menu.h"
#endif

class Game
{
private:
    // variables
    WindowHandler *window;
    std::vector<Enemy *> enemies;
    std::vector<Tower *> towers;
    int level;
    int playerHp;
    int money;
    bool endGame;
    std::vector<sf::Vector2f> enemyPath;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::ConvexShape selectBox;
    bool cursorOnMap;

    // functions
    /**
     * @brief Initialize game variables
     *
     * Creates new WindowHandler object and initializes default starting values:
     * level = 1, endGame = false, playerHp = 100, money = 100
     */
    void initVariables();

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
     * @brief Add enemy to the game
     * @param enemyType Character representing enemy type
     *
     *  Used in loadLevel function to add enemies to the game by their shortened name
     * (P - Peasant, W - Warrior, H - HeavyKnight)
     */
    void addEnemy(char enemyType);

    /**
     * @brief Load map image
     *
     * Loads map image from `textures` directory and sets it as background
     */
    void initWorld();

    /**
     * @brief Updates position of selectBox
     *
     * If hovering over a map, change position of selectBox accordingly
     */
    void updateSelectBox();

    void placeTower();

    bool isCursorOnMap();

    sf::Vector2f getCursorProjection();

public:
    // constructor and destructor
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

    // functions
    /**
     * @brief Update window
     *
     * Calls `WindowHandler::update` function
     */
    void update();

    /**
     * @brief Render all objects
     *
     * Calls `WindowHandler::render` passing background and all objects to render
     */
    void render();

    /**
     * @brief Start game loop
     *
     * Opens start menu and starts game loop
     */
    void startGame();

    /**
     * @brief Game loop
     *
     * Calls `update` and `render` functions in a loop while game is running
     */
    void gameLoop();

    /**
     * @brief Start menu
     *
     * Opens start menu and waits for user to start a game, open settings or exit the game
     */
    void startingScreen();
};