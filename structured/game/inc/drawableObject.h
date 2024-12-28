#pragma once
#include <SFML/Graphics.hpp>

/**
 * @brief Interface for drawable objects
 *
 * Interface extending sf::Drawable by adding getPosition method used for sorting objects.
 */
class DrawableObject : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

public:
    virtual sf::Vector2f getPosition() const;
};