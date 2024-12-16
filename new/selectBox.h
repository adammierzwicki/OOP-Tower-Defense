#pragma once
#include <SFML/Graphics.hpp>
#include "drawableObject.h"

/**
 * @brief Class for drawing tower select box on screen
 *
 * Contains methods for drawing select box on screen and setting its color and position
 */
class SelectBox : public DrawableObject
{
private:
    //-----------------------------------
    //             Attributes
    //-----------------------------------

    sf::ConvexShape shape;
    sf::Color color;

    //-----------------------------------
    //          Private methods
    //-----------------------------------

    /**
     * @brief Draw select box on screen
     *
     * @param target Render target
     * @param states Render states
     *
     * Draws select box on screen with given render states.
     *
     * Implemented from sf::Drawable interface
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

public:
    //-----------------------------------
    //     Constructor and destructor
    //-----------------------------------

    /**
     * @brief Construct a new Select Box object
     *
     * Initializes select box shape and color
     */
    SelectBox();

    /**
     * @brief Destroy the Select Box object
     *
     * Default destructor for SelectBox object
     */
    ~SelectBox();

    //-----------------------------------
    //             Accessors
    //-----------------------------------

    /**
     * @brief Get select box position
     * @return Select box position
     *
     * Get select box position in sf::Vector2f format.
     * 
     * Implemented from DrawableObject interface
     */
    sf::Vector2f getPosition();

    //-----------------------------------
    //             Modifiers
    //-----------------------------------

    /**
     * @brief Set select box color
     * @param color Select box color
     *
     * Set select box color to color given in sf::Color format
     */
    void setColor(sf::Color color);

    /**
     * @brief Set select box position
     * @param position Select box position
     *
     * Set select box position to position given in sf::Vector2f format
     */
    void setPosition(sf::Vector2f position);
};