#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class EndGame
{
private:
    sf::RenderWindow *window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int selectedItemIndex;
    sf::Font font;
    std::string message;
    std::vector<sf::Text> items;

public:
    EndGame(sf::RenderWindow *window, std::string message);
    ~EndGame();

    void render();
    void handleInput(bool &isRunning);
};
