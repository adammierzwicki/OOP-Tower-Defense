#include <gtest/gtest.h>
#include "../../game/inc/tower.h"
#include "../../game/inc/enemy.h"

class TowerTest : public testing::Test
{
protected:
    Tower *tower;   

    void SetUp() override
    {
        tower = new Tower();
    }

    void TearDown() override
    {
        delete tower;
    }
};

