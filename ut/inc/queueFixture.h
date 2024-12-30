#include <gtest/gtest.h>
#include "../../game/inc/customQueue.h"

class CharQueueTest : public testing::Test
{
protected:
    Queue<char> *queue;

    void SetUp() override
    {
        queue = new Queue<char>();
    }

    void TearDown() override
    {
        delete queue;
    }
};

class IntQueueTest : public testing::Test
{
protected:
    Queue<int> *queue;

    void SetUp() override
    {
        queue = new Queue<int>();
    }

    void TearDown() override
    {
        delete queue;
    }
};