#include "../inc/animation.h"
#include <iostream>

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    this->totalTime = 0.0f;
    this->currentImage.x = 0;

    this->uvRect.width = texture->getSize().x / float(imageCount.x);
    this->uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {}

//-----------------------------------
//             Accessors
//-----------------------------------

sf::IntRect Animation::getUVrect() { return this->uvRect; }

//-----------------------------------
//          Public methods
//-----------------------------------

void Animation::update(int row, float deltaTime)
{
    this->currentImage.y = row;
    this->totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        // if (currentImage.x >= imageCount.x)
        if (currentImage.x >= 8)
        {
            currentImage.x = 0;
        }
    }

    this->uvRect.left = currentImage.x * uvRect.width;
    this->uvRect.top = currentImage.y * uvRect.height;
}