#include <gtest/gtest.h>
#include "../../game/inc/tower.h"
#include "../../game/inc/enemy.h"

class TowerTest : public testing::Test
{
protected:
    Tower *tower;
    Enemy *enemy;

    void SetUp() override
    {
        tower = new Tower();
        enemy = new Peasant(true);
    }

    void TearDown() override
    {
        delete tower;
        delete enemy;
    }
};
