#include <iostream>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    int hp;
    float speed;
    sf::Vector2f position;
    std::string enemy_type;

public:
    Enemy(std::string enemy_type, int hp, float speed);
    Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f);
    ~Enemy();

    int getHp();
    int getSpeed();
    std::string getType();
    sf::Vector2f getPosition();
    sf::RectangleShape shape;
    sf::Texture texture;

    void setStartPosition(sf::Vector2f position);

    void takeDamage(int damage);
    bool isDead();

    void update();
    void render(sf::RenderTarget *target);
    // void move();
    // todo: someType animate();
};

class Peasant : public Enemy
{
private:
    void initVariables();
    void initShape();

public:
    Peasant();
    ~Peasant();
};

class Warrior : public Enemy
{
private:
    // image = "enemy2.png";
public:
    Warrior();
    ~Warrior();
};

class HeavyKnight : public Enemy
{
private:
    // image = "enemy3.png";
public:
    HeavyKnight();
    ~HeavyKnight();
};
