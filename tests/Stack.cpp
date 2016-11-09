#include <gtest/gtest.h>
#include <Stack.h>

TEST(StackTests, canCreateEmptyStack) {
    Stack<int> stack;
    unsigned long size = stack.size();
    EXPECT_EQ(size, 0);
}

TEST(StackTests, canPushTempElement) {
    Stack<int> stack;
    stack.push(439);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.front(), 439);
}

TEST(StackTests, canPushElement) {
    Stack<int> stack;
    auto element = 5423;
    stack.push(element);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.front(), 5423);
}

TEST(StackTests, canPushMoreElements) {
    Stack<int> stack;
    stack.push(33);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.front(), 33);
    stack.push(21);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.front(), 21);
    stack.push(594);
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.front(), 594);
    stack.push(37);
    EXPECT_EQ(stack.size(), 4);
    EXPECT_EQ(stack.front(), 37);
}

TEST(StackTests, canPushAndPopElement) {
    Stack<int> stack;
    stack.push(439);
    stack.pop();
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTests, canPushAndPopMoreElements) {
    Stack<int> stack;
    stack.push(439);
    stack.push(599);
    stack.push(238);
    stack.push(70);
    stack.push(43);
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.front(), 43);
    stack.pop();
    EXPECT_EQ(stack.size(), 4);
    EXPECT_EQ(stack.front(), 70);
    stack.pop();
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.front(), 238);
    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.front(), 599);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.front(), 439);
    stack.pop();
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTests, canPushAndPopByShiftOperators) {
    Stack<int> stack;
    int temp = -4;
    stack << temp;
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.front(), -4);
    stack << 93 << 24;
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.front(), 24);
    stack << 325 << 0 << 3267;
    EXPECT_EQ(stack.size(), 6);
    EXPECT_EQ(stack.front(), 3267);
    int result[6];
    stack >> result[0];
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.front(), 0);
    stack >> result[1] >> result[2] >> result[3] >> result[4] >> result[5];
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(result[0], 3267);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 325);
    EXPECT_EQ(result[3], 24);
    EXPECT_EQ(result[4], 93);
    EXPECT_EQ(result[5], -4);
}
