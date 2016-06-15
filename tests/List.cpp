//
// Created by maciek on 13.06.16.
//

#include <boost/test/unit_test.hpp>
#include <List.h>
#include <Move.h>

BOOST_AUTO_TEST_SUITE(ListTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyList)
    {
        List<int> list;
        BOOST_CHECK_EQUAL(list.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canThrowExceptionOnFrontAccess)
    {
        List<int> list;
        BOOST_CHECK_THROW(list.front(), EmptyContainerException);
    }

    BOOST_AUTO_TEST_CASE(canThrowExceptionOnBackAccess)
    {
        List<int> list;
        BOOST_CHECK_THROW(list.back(), EmptyContainerException);
    }

    BOOST_AUTO_TEST_CASE(canThrowExceptionOnPopBack)
    {
        List<int> list;
        BOOST_CHECK_THROW(list.pop_back(), EmptyContainerException);
    }

    BOOST_AUTO_TEST_CASE(canThrowExceptionOnPopFront)
    {
        List<int> list;
        BOOST_CHECK_THROW(list.pop_front(), EmptyContainerException);
    }

    BOOST_AUTO_TEST_CASE(canAddFrontItem)
    {
        List<int> list;
        list.push_front(2);
        BOOST_CHECK_EQUAL(list.size(), 1);
        BOOST_CHECK_EQUAL(list.front(), 2);
    }

    BOOST_AUTO_TEST_CASE(canAddTwoFrontItems)
    {
        List<int> list;
        list.push_front(2);
        list.push_front(1);
        BOOST_CHECK_EQUAL(list.size(), 2);
        BOOST_CHECK_EQUAL(list.front(), 1);
        BOOST_CHECK_EQUAL(list.back(), 2);
    }

    BOOST_AUTO_TEST_CASE(canAddBackItem)
    {
        List<int> list;
        list.push_back(4);
        BOOST_CHECK_EQUAL(list.size(), 1);
        BOOST_CHECK_EQUAL(list.back(), 4);
    }

    BOOST_AUTO_TEST_CASE(canAddBackTwoItems)
    {
        List<int> list;
        list.push_back(8);
        list.push_back(3);
        BOOST_CHECK_EQUAL(list.size(), 2);
        BOOST_CHECK_EQUAL(list.front(), 8);
        BOOST_CHECK_EQUAL(list.back(), 3);
    }

    BOOST_AUTO_TEST_CASE(canAccessElements)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);

        int result[3];
        int i = 0;
        for (auto it : list)
            result[i++] = it;
        BOOST_CHECK_EQUAL(result[0], 1);
        BOOST_CHECK_EQUAL(result[1], 2);
        BOOST_CHECK_EQUAL(result[2], 3);
    }

    BOOST_AUTO_TEST_CASE(canPopBack)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);

        BOOST_CHECK_EQUAL(list.front(), 1);
        list.pop_back();
        BOOST_CHECK_EQUAL(list.size(), 2);
        BOOST_CHECK_EQUAL(list.back(), 2);
        BOOST_CHECK_EQUAL(list.front(), 1);
    }

    BOOST_AUTO_TEST_CASE(canPopFront)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);
        list.push_front(10);
        BOOST_CHECK_EQUAL(list.front(), 10);
        list.pop_front();
        BOOST_CHECK_EQUAL(list.size(), 3);
        BOOST_CHECK_EQUAL(list.back(), 3);
        BOOST_CHECK_EQUAL(list.front(), 1);
    }

    BOOST_AUTO_TEST_CASE(canBeResized)
    {
        List<int> list;
        list.resize(20);
        BOOST_CHECK_EQUAL(list.size(), 20);
        for (auto &it : list)
            it = 38;
        BOOST_CHECK_EQUAL(list.front(), 38);
        BOOST_CHECK_EQUAL(list.back(), 38);
        list.resize(2);
        BOOST_CHECK_EQUAL(list.front(), 38);
        BOOST_CHECK_EQUAL(list.back(), 38);
        BOOST_CHECK_EQUAL(list.size(), 2);
    }

    BOOST_AUTO_TEST_CASE(canIncrementIterator)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);
        list.push_front(10);
        auto it = list.begin();
        BOOST_CHECK_EQUAL(*it, 10);
        it++;
        BOOST_CHECK_EQUAL(*it, 1);
        ++it;
        BOOST_CHECK_EQUAL(*it, 2);
        it = list.begin();
        *it = 34;
        BOOST_CHECK_EQUAL(*it, 34);
        BOOST_CHECK_EQUAL(list.front(), 34);
    }

    BOOST_AUTO_TEST_CASE(canDecrementIterator)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);
        list.push_front(10);
        auto it = list.end();
        it--;
        BOOST_CHECK_EQUAL(*it, 3);
        --it;
        BOOST_CHECK_EQUAL(*it, 2);
    }

    BOOST_AUTO_TEST_CASE(canIncrementAndDecrementIterator)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);
        list.push_front(10);
        auto it = list.begin();
        BOOST_CHECK_EQUAL(*it, 10);
        it++;
        BOOST_CHECK_EQUAL(*it, 1);
        it--;
        BOOST_CHECK_EQUAL(*it, 10);
    }

    BOOST_AUTO_TEST_CASE(canCompareIterators)
    {
        List<int> list;
        list.push_back(3);
        list.push_front(2);
        list.push_front(1);
        list.push_front(10);
        auto it1 = list.begin();
        auto it2 = it1;
        BOOST_CHECK_EQUAL(it1 == it2, true);
        it2++;
        BOOST_CHECK_EQUAL(it1 != it2, true);
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByCopy)
    {
        List<int> list1;
        list1.push_back(3);
        list1.push_front(2);
        list1.push_front(1);
        list1.push_front(10);
        List<int> list2(list1);
        BOOST_CHECK_EQUAL(list1.front(), 10);
        BOOST_CHECK_EQUAL(list2.front(), 10);
        BOOST_CHECK_EQUAL(list2.back(), 3);
    }

    BOOST_AUTO_TEST_CASE(canBeAssigned)
    {
        List<int> list1;
        list1.push_back(3);
        list1.push_front(2);
        list1.push_front(1);
        list1.push_front(10);
        List<int> list2;
        list2.push_back(99);
        list2.push_back(120);
        list2 = list1;
        BOOST_CHECK_EQUAL(list1.size(), 4);
        BOOST_CHECK_EQUAL(list2.size(), 4);
        BOOST_CHECK_EQUAL(list1.front(), 10);
        BOOST_CHECK_EQUAL(list2.front(), 10);
        BOOST_CHECK_EQUAL(list2.back(), 3);
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByMove)
    {
        List<int> list1;
        list1.push_back(3);
        list1.push_front(2);
        list1.push_front(1);
        list1.push_front(10);
        List<int> list2(move(list1));
        int result[4];
        int i = 0;
        for (auto it : list2)
            result[i++] = it;
        BOOST_CHECK_EQUAL(list1.size(), 0);
        BOOST_CHECK_EQUAL(list2.size(), 4);
        BOOST_CHECK_EQUAL(list2.front(), 10);
        BOOST_CHECK_EQUAL(list2.back(), 3);
        BOOST_CHECK_EQUAL(result[0], 10);
        BOOST_CHECK_EQUAL(result[1], 1);
        BOOST_CHECK_EQUAL(result[2], 2);
        BOOST_CHECK_EQUAL(result[3], 3);
    }

    BOOST_AUTO_TEST_CASE(canBeMoved)
    {
        List<int> list1;
        list1.push_back(3);
        list1.push_front(2);
        list1.push_front(1);
        list1.push_front(10);
        List<int> list2;
        list2.push_back(4);
        list2 = move(list1);
        int result[4];
        int i = 0;
        for (auto it : list2)
            result[i++] = it;
        BOOST_CHECK_EQUAL(list1.size(), 0);
        BOOST_CHECK_EQUAL(list2.size(), 4);
        BOOST_CHECK_EQUAL(list2.front(), 10);
        BOOST_CHECK_EQUAL(list2.back(), 3);
        BOOST_CHECK_EQUAL(result[0], 10);
        BOOST_CHECK_EQUAL(result[1], 1);
        BOOST_CHECK_EQUAL(result[2], 2);
        BOOST_CHECK_EQUAL(result[3], 3);
    }

    BOOST_AUTO_TEST_CASE(canEraseSingleElement)
    {
        List<int> list;
        list.push_front(43);
        list.push_front(-59);
        list.push_back(23);
        auto it = list.begin();
        ++it;
        BOOST_CHECK_EQUAL(list.front(), -59);
        BOOST_CHECK_EQUAL(list.back(), 23);
        list.erase(it);
        BOOST_CHECK_EQUAL(list.size(), 2);
        BOOST_CHECK_EQUAL(list.front(), -59);
        BOOST_CHECK_EQUAL(list.back(), 23);
        list.erase(list.begin());
        BOOST_CHECK_EQUAL(list.size(), 1);
        BOOST_CHECK_EQUAL(list.front(), 23);
        BOOST_CHECK_EQUAL(list.back(), 23);
        list.erase(list.end()--);
        BOOST_CHECK_EQUAL(list.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canEraseElements)
    {
        List<int> list;
        list.push_front(43);
        list.push_front(-59);
        list.push_back(23);
        list.push_back(13);
        list.erase(++list.begin(), list.end());
        BOOST_CHECK_EQUAL(list.size(), 1);
        BOOST_CHECK_EQUAL(list.front(), -59);
        BOOST_CHECK_EQUAL(list.back(), -59);
        list.erase(list.begin(), list.end());
        BOOST_CHECK_EQUAL(list.size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()

