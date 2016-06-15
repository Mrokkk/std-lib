//
// Created by maciek on 15.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Queue.h>

BOOST_AUTO_TEST_SUITE(QueueTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyQueue)
    {
        Queue<int> queue;
        unsigned long size = queue.size();
        BOOST_CHECK_EQUAL(size, 0);
    }

    BOOST_AUTO_TEST_CASE(canPushTempElement)
    {
        Queue<int> queue;
        queue.push(439);
        BOOST_CHECK_EQUAL(queue.size(), 1);
        BOOST_CHECK_EQUAL(queue.front(), 439);
    }

    BOOST_AUTO_TEST_CASE(canPushElement)
    {
        Queue<int> queue;
        auto element = 5423;
        queue.push(element);
        BOOST_CHECK_EQUAL(queue.size(), 1);
        BOOST_CHECK_EQUAL(queue.front(), 5423);
    }

    BOOST_AUTO_TEST_CASE(canPushMoreElements)
    {
        Queue<int> queue;
        queue.push(33);
        BOOST_CHECK_EQUAL(queue.size(), 1);
        BOOST_CHECK_EQUAL(queue.front(), 33);
        queue.push(21);
        BOOST_CHECK_EQUAL(queue.size(), 2);
        BOOST_CHECK_EQUAL(queue.front(), 33);
        queue.push(594);
        BOOST_CHECK_EQUAL(queue.size(), 3);
        BOOST_CHECK_EQUAL(queue.front(), 33);
        queue.push(37);
        BOOST_CHECK_EQUAL(queue.size(), 4);
        BOOST_CHECK_EQUAL(queue.front(), 33);
    }

    BOOST_AUTO_TEST_CASE(canPushAndPopElement)
    {
        Queue<int> queue;
        queue.push(439);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canPushAndPopMoreElements)
    {
        Queue<int> queue;
        queue.push(439);
        queue.push(599);
        queue.push(238);
        queue.push(70);
        queue.push(43);
        BOOST_CHECK_EQUAL(queue.size(), 5);
        BOOST_CHECK_EQUAL(queue.front(), 439);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 4);
        BOOST_CHECK_EQUAL(queue.front(), 599);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 3);
        BOOST_CHECK_EQUAL(queue.front(), 238);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 2);
        BOOST_CHECK_EQUAL(queue.front(), 70);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 1);
        BOOST_CHECK_EQUAL(queue.front(), 43);
        queue.pop();
        BOOST_CHECK_EQUAL(queue.size(), 0);
    }


BOOST_AUTO_TEST_SUITE_END()