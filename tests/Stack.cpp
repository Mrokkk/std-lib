//
// Created by maciek on 14.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Stack.h>

BOOST_AUTO_TEST_SUITE(StackTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyStack)
    {
        Stack<int> stack;
        unsigned long size = stack.size();
        BOOST_CHECK_EQUAL(size, 0);
    }

    BOOST_AUTO_TEST_CASE(canPushTempElement)
    {
        Stack<int> stack;
        stack.push(439);
        BOOST_CHECK_EQUAL(stack.size(), 1);
        BOOST_CHECK_EQUAL(stack.front(), 439);
    }

    BOOST_AUTO_TEST_CASE(canPushElement)
    {
        Stack<int> stack;
        auto element = 5423;
        stack.push(element);
        BOOST_CHECK_EQUAL(stack.size(), 1);
        BOOST_CHECK_EQUAL(stack.front(), 5423);
    }

    BOOST_AUTO_TEST_CASE(canPushMoreElements)
    {
        Stack<int> stack;
        stack.push(33);
        BOOST_CHECK_EQUAL(stack.size(), 1);
        BOOST_CHECK_EQUAL(stack.front(), 33);
        stack.push(21);
        BOOST_CHECK_EQUAL(stack.size(), 2);
        BOOST_CHECK_EQUAL(stack.front(), 21);
        stack.push(594);
        BOOST_CHECK_EQUAL(stack.size(), 3);
        BOOST_CHECK_EQUAL(stack.front(), 594);
        stack.push(37);
        BOOST_CHECK_EQUAL(stack.size(), 4);
        BOOST_CHECK_EQUAL(stack.front(), 37);
    }

    BOOST_AUTO_TEST_CASE(canPushAndPopElement)
    {
        Stack<int> stack;
        stack.push(439);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canPushAndPopMoreElements)
    {
        Stack<int> stack;
        stack.push(439);
        stack.push(599);
        stack.push(238);
        stack.push(70);
        stack.push(43);
        BOOST_CHECK_EQUAL(stack.size(), 5);
        BOOST_CHECK_EQUAL(stack.front(), 43);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 4);
        BOOST_CHECK_EQUAL(stack.front(), 70);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 3);
        BOOST_CHECK_EQUAL(stack.front(), 238);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 2);
        BOOST_CHECK_EQUAL(stack.front(), 599);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 1);
        BOOST_CHECK_EQUAL(stack.front(), 439);
        stack.pop();
        BOOST_CHECK_EQUAL(stack.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canPushAndPopByShiftOperators)
    {
        Stack<int> stack;
        int temp = -4;
        stack << temp;
        BOOST_CHECK_EQUAL(stack.size(), 1);
        BOOST_CHECK_EQUAL(stack.front(), -4);
        stack << 93 << 24;
        BOOST_CHECK_EQUAL(stack.size(), 3);
        BOOST_CHECK_EQUAL(stack.front(), 24);
        stack << 325 << 0 << 3267;
        BOOST_CHECK_EQUAL(stack.size(), 6);
        BOOST_CHECK_EQUAL(stack.front(), 3267);
        int result[6];
        stack >> result[0];
        BOOST_CHECK_EQUAL(stack.size(), 5);
        BOOST_CHECK_EQUAL(stack.front(), 0);
        stack >> result[1] >> result[2] >> result[3] >> result[4] >> result[5];
        BOOST_CHECK_EQUAL(stack.size(), 0);
        BOOST_CHECK_EQUAL(result[0], 3267);
        BOOST_CHECK_EQUAL(result[1], 0);
        BOOST_CHECK_EQUAL(result[2], 325);
        BOOST_CHECK_EQUAL(result[3], 24);
        BOOST_CHECK_EQUAL(result[4], 93);
        BOOST_CHECK_EQUAL(result[5], -4);
    }

BOOST_AUTO_TEST_SUITE_END()