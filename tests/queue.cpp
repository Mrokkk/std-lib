#include <queue.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(queue, can_create_empty_queue)
{
    queue<int> queue;
    auto size = queue.size();
    REQUIRE(size == 0);
}

TEST(queue, can_push_temp_element)
{
    queue<int> queue;
    queue.push(439);
    REQUIRE(queue.size() == 1);
    REQUIRE_EQ(queue.front(), 439);
}

TEST(queue, can_push_element)
{
    queue<int> queue;
    auto element = 5423;
    queue.push(element);
    REQUIRE(queue.size() == 1);
    REQUIRE_EQ(queue.front(), 5423);
}

TEST(queue, can_push_more_elements)
{
    queue<int> queue;
    queue.push(33);
    REQUIRE(queue.size() == 1);
    REQUIRE_EQ(queue.front(), 33);
    queue.push(21);
    REQUIRE(queue.size() == 2);
    REQUIRE_EQ(queue.front(), 33);
    queue.push(594);
    REQUIRE(queue.size() == 3);
    REQUIRE_EQ(queue.front(), 33);
    queue.push(37);
    REQUIRE(queue.size() == 4);
    REQUIRE_EQ(queue.front(), 33);
}

TEST(queue, can_push_and_pop_element)
{
    queue<int> queue;
    queue.push(439);
    queue.pop();
    REQUIRE(queue.size() == 0);
}

TEST(queue, can_push_and_pop_more_elements)
{
    queue<int> queue;
    queue.push(439);
    queue.push(599);
    queue.push(238);
    queue.push(70);
    queue.push(43);
    REQUIRE(queue.size() == 5);
    REQUIRE_EQ(queue.front(), 439);
    queue.pop();
    REQUIRE(queue.size() == 4);
    REQUIRE_EQ(queue.front(), 599);
    queue.pop();
    REQUIRE(queue.size() == 3);
    REQUIRE_EQ(queue.front(), 238);
    queue.pop();
    REQUIRE(queue.size() == 2);
    REQUIRE_EQ(queue.front(), 70);
    queue.pop();
    REQUIRE(queue.size() == 1);
    REQUIRE_EQ(queue.front(), 43);
    queue.pop();
    REQUIRE(queue.size() == 0);
}

TEST(queue, can_push_and_pop_by_shift_operators)
{
    queue<int> queue;
    int temp = -4;
    queue << temp;
    REQUIRE(queue.size() == 1);
    REQUIRE_EQ(queue.front(), -4);
    queue << 93 << 24;
    REQUIRE(queue.size() == 3);
    REQUIRE_EQ(queue.front(), -4);
    queue << 325 << 0 << 3267;
    REQUIRE(queue.size() == 6);
    REQUIRE_EQ(queue.front(), -4);
    int result[6];
    queue >> result[0];
    REQUIRE(queue.size() == 5);
    REQUIRE_EQ(queue.front(), 93);
    queue >> result[1] >> result[2] >> result[3] >> result[4] >> result[5];
    REQUIRE(queue.size() == 0);
    REQUIRE_EQ(result[0], -4);
    REQUIRE_EQ(result[1], 93);
    REQUIRE_EQ(result[2], 24);
    REQUIRE_EQ(result[3], 325);
    REQUIRE_EQ(result[4], 0);
    REQUIRE_EQ(result[5], 3267);
}
