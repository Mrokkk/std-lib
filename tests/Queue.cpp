//
// Created by maciek on 15.06.16.
//

#include <gtest/gtest.h>
#include <Queue.h>

TEST(QueueTests, canCreateEmptyQueue)
{
    Queue<int> queue;
    unsigned long size = queue.size();
    EXPECT_EQ(size, 0);
}

TEST(QueueTests, canPushTempElement)
{
    Queue<int> queue;
    queue.push(439);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 439);
}

TEST(QueueTests, canPushElement)
{
    Queue<int> queue;
    auto element = 5423;
    queue.push(element);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 5423);
}

TEST(QueueTests, canPushMoreElements)
{
    Queue<int> queue;
    queue.push(33);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 33);
    queue.push(21);
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 33);
    queue.push(594);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 33);
    queue.push(37);
    EXPECT_EQ(queue.size(), 4);
    EXPECT_EQ(queue.front(), 33);
}

TEST(QueueTests, canPushAndPopElement)
{
    Queue<int> queue;
    queue.push(439);
    queue.pop();
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTests, canPushAndPopMoreElements)
{
    Queue<int> queue;
    queue.push(439);
    queue.push(599);
    queue.push(238);
    queue.push(70);
    queue.push(43);
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 439);
    queue.pop();
    EXPECT_EQ(queue.size(), 4);
    EXPECT_EQ(queue.front(), 599);
    queue.pop();
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 238);
    queue.pop();
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 70);
    queue.pop();
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 43);
    queue.pop();
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTests, canPushAndPopByShiftOperators)
{
    Queue<int> queue;
    int temp = -4;
    queue << temp;
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), -4);
    queue << 93 << 24;
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), -4);
    queue << 325 << 0 << 3267;
    EXPECT_EQ(queue.size(), 6);
    EXPECT_EQ(queue.front(), -4);
    int result[6];
    queue >> result[0];
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 93);
    queue >> result[1] >> result[2] >> result[3] >> result[4] >> result[5];
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(result[0], -4);
    EXPECT_EQ(result[1], 93);
    EXPECT_EQ(result[2], 24);
    EXPECT_EQ(result[3], 325);
    EXPECT_EQ(result[4], 0);
    EXPECT_EQ(result[5], 3267);
}
