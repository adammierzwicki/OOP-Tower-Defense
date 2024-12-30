#include <gtest/gtest.h>
#include "../inc/towerFixture.h"


TEST_F(TowerTest, EnemyInRange)
{
    tower->setPosition(sf::Vector2f(10.f, 10.f));
    tower->setRange(10);
    tower->getRangeCircle()->setRadius(tower->getRange());
    tower->getRangeCircle()->setOrigin(tower->getRange(), tower->getRange());
    tower->getRangeCircle()->setPosition(tower->getPosition());
    tower->getRangeCircle()->setScale(1.8f, 1.f);

    enemy->setStartPosition(sf::Vector2f(5.f, 5.f));
    enemy->getPosition();

    ASSERT_TRUE(tower->enemyInRange(enemy));
}

TEST_F(TowerTest, EnemyOutOfRange)
{
    tower->setPosition(sf::Vector2f(10.f, 10.f));
    tower->setRange(10);
    tower->getRangeCircle()->setRadius(tower->getRange());
    tower->getRangeCircle()->setOrigin(tower->getRange(), tower->getRange());
    tower->getRangeCircle()->setPosition(tower->getPosition());
    tower->getRangeCircle()->setScale(1.8f, 1.f);

    enemy->setStartPosition(sf::Vector2f(0.f, 0.f));
    enemy->getPosition();

    ASSERT_FALSE(tower->enemyInRange(enemy));
}

TEST_F(TowerTest, EnemyOnEdgeOfRange)
{
    tower->setPosition(sf::Vector2f(10.f, 10.f));
    tower->setRange(10);
    tower->getRangeCircle()->setRadius(tower->getRange());
    tower->getRangeCircle()->setOrigin(tower->getRange(), tower->getRange());
    tower->getRangeCircle()->setPosition(tower->getPosition());
    tower->getRangeCircle()->setScale(1.8f, 1.f);

    enemy->setStartPosition(sf::Vector2f(10.f, 20.f));
    ASSERT_TRUE(tower->enemyInRange(enemy));

    enemy->setStartPosition(sf::Vector2f(10.f, 0.f));
    ASSERT_TRUE(tower->enemyInRange(enemy));
}