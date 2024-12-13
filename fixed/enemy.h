#include <iostream>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

/**
 * @brief Base class for all enemies
 * @implements sf::Drawable
 *
 * Contains basic attributes and methods for all enemies
 */
class Enemy : public sf::Drawable
{
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    int hp;
    float speed;
    sf::Vector2f position;
    std::string enemy_type;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Draw enemy on screen
     *
     * @param target Render target
     * @param states Render states
     *
     * Draws enemy sprite on screen with given render states.
     *
     * Implemented from sf::Drawable interface
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

protected:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape shape;

    //-----------------------------------
    //          Protected methods
    //-----------------------------------

    virtual void initShape();

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Enemy object at position (0, 0)
     * @param enemy_type Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     *
     * Construct a new Enemy object with given type, hp and speed at position (0, 0)
     */
    Enemy(std::string enemy_type, int hp, float speed);

    /**
     * @brief Construct a new Enemy object at given position
     * @param enemy_type Type of enemy
     * @param hp Enemy hp
     * @param speed Enemy movement speed
     * @param position Enemy start position
     *
     * Construct a new Enemy object with given type, hp, speed and start position
     */
    Enemy(std::string enemy_type, int hp, float speed, sf::Vector2f position);

    /**
     * @brief Destroy the Enemy object
     *
     * Default destructor for Enemy object
     */
    ~Enemy();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get enemy hp
     * @return Enemy hp
     */
    int getHp();

    /**
     * @brief Get current enemy position
     * @return Enemy position
     */
    sf::Vector2f getPosition();

    /**
     * @brief Get enemy movement speed
     * @return Enemy speed
     */
    int getSpeed();

    /**
     * @brief Get enemy type
     * @return Enemy type
     */
    std::string getType();

    /**
     * @brief Check if enemy is dead
     * @return True if enemy is dead, false otherwise
     */
    bool isDead();

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set enemy start position
     * @param position Start position
     *
     * Set enemy start position to position given in sf::Vector2f format
     */
    void setStartPosition(sf::Vector2f position);

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Deal damage to enemy
     * @param damage Amount of damage to deal
     *
     * Decrease enemy hp by damage amount and check if enemy is dead
     */
    void takeDamage(int damage);

    /**
     * @brief Update enemy position
     *
     * Moves enemy in the direction of the path
     */
    void update();

    // todo: someType animate();
};

class Peasant : public Enemy
{
private:
    void initShape() override;

public:
    Peasant();
    ~Peasant();
};

class Warrior : public Enemy
{
private:
    // void initShape() override;
public:
    Warrior();
    ~Warrior();
};

class HeavyKnight : public Enemy
{
private:
    // void initShape() override;
public:
    HeavyKnight();
    ~HeavyKnight();
};
