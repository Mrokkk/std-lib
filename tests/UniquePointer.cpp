//
// Created by maciek on 14.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Pointer.h>
#include <Move.h>

BOOST_AUTO_TEST_SUITE(UniquePointerTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyPointer)
    {
        UniquePointer<int> ptr;
        BOOST_CHECK_EQUAL(ptr.get(), (void *) NULL);
    }

    BOOST_AUTO_TEST_CASE(canCreateValidPointer)
    {
        SharedPointer<int> ptr(new int(4));
        BOOST_CHECK_EQUAL(*ptr, 4);
    }

    BOOST_AUTO_TEST_CASE(canBeAssigned)
    {
        UniquePointer<int> ptr;
        ptr = makeUnique<int>(5);
        BOOST_CHECK_EQUAL(*ptr, 5);
    }

    BOOST_AUTO_TEST_CASE(canBeMoved)
    {
        auto ptr1 = makeUnique<int>(10);
        UniquePointer<int> ptr2;
        ptr2 = move(ptr1);
        BOOST_CHECK_EQUAL(*ptr2, 10);
        BOOST_CHECK_EQUAL(ptr1.get(), (void *) NULL);
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedFromOther)
    {
        auto ptr1 = makeUnique<int>(10);
        UniquePointer<int> ptr2(move(ptr1));
        BOOST_CHECK_EQUAL(*ptr2, 10);
        BOOST_CHECK_EQUAL(ptr1.get(), (void *) NULL);
    }

BOOST_AUTO_TEST_SUITE_END()