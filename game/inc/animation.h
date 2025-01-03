#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Class handling animation
 *
 * Class updating uvRect of enemy sprite to animate it
 */
class Animation {
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float switchTime;
    float totalTime;
    sf::IntRect uvRect;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Animation object
     * @param texture Enemy texture
     * @param imageCount Number of images in the texture
     * @param switchTime Time between animation frames
     *
     * Initializes all class variables
     */
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    /**
     * @brief Default destructor
     */
    ~Animation();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get uvRect of enemy sprite
     * @return uvRect of enemy sprite
     */
    sf::IntRect getUVrect() const;

    //-----------------------------------
    //          Public methods
    //-----------------------------------

    /**
     * @brief Update uvRect of enemy sprite
     * @param row Row corresponding to current enemy direction
     * @param deltaTime Time passed since last frame
     *
     * Updates uvRect coordinates based on enemy direction and time passed
     */
    void update(unsigned int row, float deltaTime);
};