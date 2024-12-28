#include <vector>
#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Font font;
    std::vector<sf::Text> menuItems;
    int selectedItemIndex;
    sf::RenderWindow *window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

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
