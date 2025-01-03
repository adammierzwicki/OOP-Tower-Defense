#include "../inc/animation.h"

#include <iostream>

//-----------------------------------
//     Constructor and destructor
//-----------------------------------

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->currentImage = sf::Vector2u(0, 0);

    this->switchTime = switchTime;
    this->totalTime = 0.f;

    this->uvRect.width = texture->getSize().x / float(imageCount.x);
    this->uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {}

//-----------------------------------
//             Accessors
//-----------------------------------

sf::IntRect Animation::getUVrect() const { return this->uvRect; }

//-----------------------------------
//          Public methods
//-----------------------------------

void Animation::update(int row, float deltaTime) {
    this->currentImage.y = row;
    this->totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        // if (currentImage.x >= imageCount.x)
        if (currentImage.x >= 8) {
            currentImage.x = 0;
        }
    }
    this->uvRect.left = currentImage.x * uvRect.width;
    this->uvRect.top = currentImage.y * uvRect.height;
}