#include <vector>
#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::RenderWindow *window;
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text title;

public:
    Menu(sf::RenderWindow *window);
    ~Menu();

    int startMenu();
    void navigateUp();
    void navigateDown();
    int getSelectedItemIndex() const;
    void render();
    void handleInput(bool &isRunning);
};