#include <stack.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(stack, can_create_empty_stack) {
    stack<int> stack;
    unsigned long size = stack.size();
    REQUIRE(size == 0);
}

TEST(stack, can_push_temp_element) {
    stack<int> stack;
    stack.push(439);
    REQUIRE(stack.size() == 1);
    REQUIRE_EQ(stack.front(), 439);
}

TEST(stack, can_push_element) {
    stack<int> stack;
    auto element = 5423;
    stack.push(element);
    REQUIRE(stack.size() == 1);
    REQUIRE_EQ(stack.front(), 5423);
}

TEST(stack, can_push_more_elements) {
    stack<int> stack;
    stack.push(33);
    REQUIRE(stack.size() == 1);
    REQUIRE_EQ(stack.front(), 33);
    stack.push(21);
    REQUIRE(stack.size() == 2);
    REQUIRE_EQ(stack.front(), 21);
    stack.push(594);
    REQUIRE(stack.size() == 3);
    REQUIRE_EQ(stack.front(), 594);
    stack.push(37);
    REQUIRE(stack.size() == 4);
    REQUIRE_EQ(stack.front(), 37);
}

TEST(stack, can_push_and_pop_element) {
    stack<int> stack;
    stack.push(439);
    stack.pop();
    REQUIRE(stack.size() == 0);
}

TEST(stack, can_push_and_pop_more_elements) {
    stack<int> stack;
    stack.push(439);
    stack.push(599);
    stack.push(238);
    stack.push(70);
    stack.push(43);
    REQUIRE(stack.size() == 5);
    REQUIRE_EQ(stack.front(), 43);
    stack.pop();
    REQUIRE(stack.size() == 4);
    REQUIRE_EQ(stack.front(), 70);
    stack.pop();
    REQUIRE(stack.size() == 3);
    REQUIRE_EQ(stack.front(), 238);
    stack.pop();
    REQUIRE(stack.size() == 2);
    REQUIRE_EQ(stack.front(), 599);
    stack.pop();
    REQUIRE(stack.size() == 1);
    REQUIRE_EQ(stack.front(), 439);
    stack.pop();
    REQUIRE(stack.size() == 0);
}

TEST(stack, can_push_and_pop_by_shift_operators) {
    stack<int> stack;
    int temp = -4;
    stack << temp;
    REQUIRE(stack.size() == 1);
    REQUIRE_EQ(stack.front(), -4);
    stack << 93 << 24;
    REQUIRE(stack.size() == 3);
    REQUIRE_EQ(stack.front(), 24);
    stack << 325 << 0 << 3267;
    REQUIRE(stack.size() == 6);
    REQUIRE_EQ(stack.front(), 3267);
    int result[6];
    stack >> result[0];
    REQUIRE(stack.size() == 5);
    REQUIRE_EQ(stack.front(), 0);
    stack >> result[1] >> result[2] >> result[3] >> result[4] >> result[5];
    REQUIRE(stack.size() == 0);
    REQUIRE_EQ(result[0], 3267);
    REQUIRE_EQ(result[1], 0);
    REQUIRE_EQ(result[2], 325);
    REQUIRE_EQ(result[3], 24);
    REQUIRE_EQ(result[4], 93);
    REQUIRE_EQ(result[5], -4);
}

