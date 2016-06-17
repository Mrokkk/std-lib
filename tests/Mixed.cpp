//
// Created by maciek on 15.06.16.
//

#include <boost/test/unit_test.hpp>
#include <List.h>
#include <Pointer.h>
#include <Algorithm.h>
#include <String.h>

BOOST_AUTO_TEST_SUITE(MixedTests)

    BOOST_AUTO_TEST_CASE(canCreateSharedPointerList)
    {
        List<SharedPointer<int>> list;
        auto ptr1 = makeShared<int>(5);
        list.push_front(ptr1);
        list.push_front(SharedPointer<int>(new int(6)));
        auto it = list.begin();
        BOOST_CHECK_EQUAL(**it, 6);
        it++;
        BOOST_CHECK_EQUAL(**it, 5);
    }

    BOOST_AUTO_TEST_CASE(canCreateStringList)
    {
        List<String> list{"String 1", "String 2", "Third String", "4th String"};
        BOOST_CHECK_EQUAL(list.size(), 4);
        BOOST_CHECK(list.front() == "String 1");
        BOOST_CHECK(list.back() == "4th String");
        for (auto &s : list)
            s = "Example";
        BOOST_CHECK(list.front() == "Example");
        BOOST_CHECK(list.back() == "Example");
    }

    BOOST_AUTO_TEST_CASE(canUseForEachOnList)
    {
        List<int> list;
        int result[3];
        list.push_front(3);
        list.push_front(5);
        list.push_front(78);
        int i = 0;
        for_each(list, [ & ](int &e) { result[i++] = e; });
        BOOST_CHECK_EQUAL(result[0], 78);
        BOOST_CHECK_EQUAL(result[1], 5);
        BOOST_CHECK_EQUAL(result[2], 3);
        BOOST_CHECK_EQUAL(count(list, 78), 1);
        for_each(list.begin(), list.end(), [ ](int &e) { e = 22; });
        i = 0;
        for_each(list, [ & ](int &e) { result[i++] = e; });
        BOOST_CHECK_EQUAL(result[0], 22);
        BOOST_CHECK_EQUAL(result[1], 22);
        BOOST_CHECK_EQUAL(result[2], 22);
    }

    BOOST_AUTO_TEST_CASE(canUseCountOnList)
    {
        List<int> list{3, 7, 8, 6, 5, 3, 7, 9, 60, 55, 8, 6};
        BOOST_CHECK_EQUAL(count(list, 3), 2);
        BOOST_CHECK_EQUAL(count(list, 9), 1);
        BOOST_CHECK_EQUAL(count(list, 20), 0);
        BOOST_CHECK_EQUAL(count_if(list, [](const int &e){ return e > 3; }), 10);
        BOOST_CHECK_EQUAL(count_if(list, [](const int &e){ return e < 3; }), 0);
        BOOST_CHECK_EQUAL(count_if(list, [](const int &e){ return 1; }), 12);
        BOOST_CHECK_EQUAL(count_if(list, [](const int &e){ return 0; }), 0);
    }

BOOST_AUTO_TEST_SUITE_END()