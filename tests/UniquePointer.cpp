//
// Created by maciek on 14.06.16.
//

#include <gtest/gtest.h>
#include <Pointer.h>
#include <Move.h>

TEST(UniquePointerTests, canCreateEmptyPointer)
{
    UniquePointer<int> ptr;
    EXPECT_EQ(ptr.get(), (void *) NULL);
}

TEST(UniquePointerTests, canCreateValidPointer)
{
    SharedPointer<int> ptr(new int(4));
    EXPECT_EQ(*ptr, 4);
}

TEST(UniquePointerTests, canBeAssigned)
{
    UniquePointer<int> ptr;
    ptr = makeUnique<int>(5);
    EXPECT_EQ(*ptr, 5);
}

TEST(UniquePointerTests, canBeMoved)
{
    auto ptr1 = makeUnique<int>(10);
    UniquePointer<int> ptr2;
    ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), (void *) NULL);
}

TEST(UniquePointerTests, canBeConstructedFromOther)
{
    auto ptr1 = makeUnique<int>(10);
    UniquePointer<int> ptr2(move(ptr1));
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), (void *) NULL);
}
