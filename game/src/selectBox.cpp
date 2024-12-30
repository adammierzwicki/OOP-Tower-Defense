#include "../inc/selectBox.h"

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

SelectBox::SelectBox()
{
    this->shape.setPointCount(4);
    this->shape.setPoint(0, sf::Vector2f(0.0f, 31.0f));
    this->shape.setPoint(1, sf::Vector2f(62.0f, 0.0f));
    this->shape.setPoint(2, sf::Vector2f(124.0f, 31.0f));
    this->shape.setPoint(3, sf::Vector2f(62.0f, 62.0f));

    this->color = sf::Color::Red;

    this->shape.setOrigin(62.0f, 0.0f);
    this->shape.setFillColor(sf::Color::Transparent);
    this->shape.setOutlineColor(color);
    this->shape.setOutlineThickness(5.0f);
}

SelectBox::~SelectBox() {}

//-----------------------------------
//          Private methods
//-----------------------------------

void SelectBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}

//-----------------------------------
//             Modifiers
//-----------------------------------

void SelectBox::setColor(sf::Color color)
{
    this->shape.setOutlineColor(color);
}

void SelectBox::setPosition(sf::Vector2f position)
{
    this->shape.setPosition(position);
}

sf::Vector2f SelectBox::getPosition() const
{
    return this->shape.getPosition();
}