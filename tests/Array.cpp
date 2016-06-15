//
// Created by maciek on 13.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Array.h>

BOOST_AUTO_TEST_SUITE(ArrayTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyString)
    {
        Array<int, 0> array;
        unsigned result = array.size();
        BOOST_CHECK_EQUAL(result, 0);
    }

    BOOST_AUTO_TEST_CASE(canCreateInitializedArray)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        BOOST_CHECK_EQUAL(array[0], 2);
        BOOST_CHECK_EQUAL(array[4], 6);
        BOOST_CHECK_EQUAL(array.size(), 5);
    }

    BOOST_AUTO_TEST_CASE(canReadElementsSequentially)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        int cArray[5] = { 0, 0, 0, 0, 0 };
        unsigned i = 0;
        for (const auto &elem : array)
            cArray[i++] = elem;
        BOOST_CHECK_EQUAL(cArray[0], 2);
        BOOST_CHECK_EQUAL(cArray[2], 4);
        BOOST_CHECK_EQUAL(cArray[4], 6);
    }

    BOOST_AUTO_TEST_CASE(canModifyElementsSequentially)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        unsigned i = 10;
        for (auto &elem : array)
            elem = i++;
        BOOST_CHECK_EQUAL(array[0], 10);
        BOOST_CHECK_EQUAL(array[2], 12);
        BOOST_CHECK_EQUAL(array[4], 14);
    }

    BOOST_AUTO_TEST_CASE(canModify)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        array[0] = 10;
        array[1] = 11;
        array[4] = 14;
        BOOST_CHECK_EQUAL(array[0], 10);
        BOOST_CHECK_EQUAL(array[1], 11);
        BOOST_CHECK_EQUAL(array[4], 14);
    }

    BOOST_AUTO_TEST_CASE(canIncrementIterator)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        auto it = array.begin();
        BOOST_CHECK_EQUAL(*it, 2);
        it++;
        BOOST_CHECK_EQUAL(*it, 3);
        ++it;
        BOOST_CHECK_EQUAL(*it, 4);
    }

    BOOST_AUTO_TEST_CASE(canDecrementIterator)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        auto it = array.end();
        it--;
        BOOST_CHECK_EQUAL(*it, 6);
        --it;
        BOOST_CHECK_EQUAL(*it, 5);
    }

    BOOST_AUTO_TEST_CASE(canIncrementAndDecrementIterator)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        auto it = array.begin();
        BOOST_CHECK_EQUAL(*it, 2);
        it++;
        BOOST_CHECK_EQUAL(*it, 3);
        it--;
        BOOST_CHECK_EQUAL(*it, 2);
    }

    BOOST_AUTO_TEST_CASE(canCompareIterators)
    {
        Array<int, 5> array{ 2, 3, 4, 5, 6 };
        auto it1 = array.begin();
        auto it2 = array.begin();
        BOOST_CHECK_EQUAL(it1 == it2, true);
        it1++;
        BOOST_CHECK_EQUAL(it1 != it2, true);
    }

BOOST_AUTO_TEST_SUITE_END()
