//
// Created by maciek on 14.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Pointer.h>

BOOST_AUTO_TEST_SUITE(SmartPointerTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyPointer)
    {
        SharedPointer<int> ptr;
        BOOST_CHECK_EQUAL(ptr.get(), (void *) NULL);
        BOOST_CHECK_EQUAL(ptr.getRefCount(), 0);
    }

    BOOST_AUTO_TEST_CASE(canCreateValidPointer)
    {
        SharedPointer<int> ptr(new int(4));
        BOOST_CHECK_NE(ptr.get(), (void *)NULL);
    }

    BOOST_AUTO_TEST_CASE(canBeDerefereced)
    {
        SharedPointer<int> ptr(new int(4));
        BOOST_CHECK_EQUAL(*ptr, 4);
    }

    BOOST_AUTO_TEST_CASE(canBeAssigned)
    {
        SharedPointer<int> ptr;
        ptr = makeShared<int>(5);
        BOOST_CHECK_EQUAL(*ptr, 5);
    }

    BOOST_AUTO_TEST_CASE(canBeCopied)
    {
        auto ptr1 = makeShared<int>(10);
        SharedPointer<int> ptr2;
        ptr2 = ptr1;
        BOOST_CHECK_EQUAL(*ptr1, 10);
        BOOST_CHECK_EQUAL(*ptr2, 10);
        BOOST_CHECK_EQUAL(ptr1.getRefCount(), 2);
        BOOST_CHECK_EQUAL(ptr2.getRefCount(), 2);
        BOOST_CHECK_EQUAL(ptr1.get(), ptr2.get());
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByCopy)
    {
        auto ptr1 = makeShared<int>(10);
        SharedPointer<int> ptr2(ptr1);
        BOOST_CHECK_EQUAL(*ptr1, 10);
        BOOST_CHECK_EQUAL(*ptr2, 10);
        BOOST_CHECK_EQUAL(ptr1.getRefCount(), 2);
        BOOST_CHECK_EQUAL(ptr2.getRefCount(), 2);
        BOOST_CHECK_EQUAL(ptr1.get(), ptr2.get());
    }

    BOOST_AUTO_TEST_CASE(canBeCastedToRawPointer)
    {
        auto ptr = makeShared<int>(10);
        int *rawPtr = ptr;
        BOOST_CHECK_EQUAL(*ptr, 10);
        BOOST_CHECK_EQUAL(*rawPtr, 10);
        BOOST_CHECK_EQUAL(ptr.get(), rawPtr);
    }

BOOST_AUTO_TEST_SUITE_END()