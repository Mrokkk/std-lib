//
// Created by maciek on 15.06.16.
//

#include <boost/test/unit_test.hpp>
#include <List.h>
#include <Pointer.h>

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

BOOST_AUTO_TEST_SUITE_END()