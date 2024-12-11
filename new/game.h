#include "windowHandler.h"
#include <vector>

class Game
{
private:
    WindowHandler *window;
    std::vector<Enemy *> enemies;
    // std::vector<Tower*> towers;
    int level;
    int playerHp;
    int money;
    bool endGame;
    std::vector<sf::Vector2f> enemyPath;
    sf::Texture backgroundTexture;
    sf::Sprite background;

    void initVariables();
    void loadLevel(int level);
    void addEnemy(char enemyType);
    void initWorld();

public:
    // constructor and destructor
    Game();
    ~Game();

    // functions
    void update();
    void render();
    void startGame();
};