#include <gtest/gtest.h>
#include "../inc/queueFixture.h"


TEST_F(IntQueueTest, PushAndPopTest) {
    queue->push(1);
    queue->push(2);
    queue->push(3);
    queue->push(4);
    queue->push(5);

    EXPECT_EQ(queue->pop(), 1);
    EXPECT_EQ(queue->pop(), 2);
    EXPECT_EQ(queue->pop(), 3);
    EXPECT_EQ(queue->pop(), 4);
    EXPECT_EQ(queue->pop(), 5);
}

TEST_F(IntQueueTest, PopFromEmptyQueueExceptionTest) {
    EXPECT_THROW(queue->pop(), std::runtime_error);
}

TEST_F(IntQueueTest, EmptyQueuePropertiesTest) {
    EXPECT_TRUE(queue->empty());
    EXPECT_EQ(queue->getSize(), 0);
}

TEST_F(IntQueueTest, NonEmptyQueuePropertiesTest) {
    queue->push(1);
    queue->push(2);
    queue->push(3);

    EXPECT_FALSE(queue->empty());
    EXPECT_EQ(queue->getSize(), 3);
}

TEST(Simple, IntQueueTest) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.pop(), 1);
    EXPECT_EQ(queue.pop(), 2);
    EXPECT_EQ(queue.pop(), 3);
}

TEST(Simple, DoubleQueueTest) {
    Queue<double> queue;
    queue.push(1.1);
    queue.push(2.2);
    queue.push(3.3);

    EXPECT_EQ(queue.pop(), 1.1);
    EXPECT_EQ(queue.pop(), 2.2);
    EXPECT_EQ(queue.pop(), 3.3);
}

TEST(Simple, StringQueueTest) {
    Queue<std::string> queue;
    queue.push("one");
    queue.push("two");
    queue.push("three");

    EXPECT_EQ(queue.pop(), "one");
    EXPECT_EQ(queue.pop(), "two");
    EXPECT_EQ(queue.pop(), "three");
}


