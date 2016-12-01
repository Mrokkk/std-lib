#include <gtest/gtest.h>
#include <pointer.h>
#include <move.h>

using namespace yacppl;

TEST(UniquePointerTests, canCreateEmptyPointer) {
    unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), (void *) NULL);
}

TEST(UniquePointerTests, canCreateValidPointer) {
    unique_ptr<int> ptr(new int(4));
    EXPECT_EQ(*ptr, 4);
}

TEST(UniquePointerTests, canBeAssigned) {
    unique_ptr<int> ptr;
    ptr = make_unique<int>(5);
    EXPECT_EQ(*ptr, 5);
}

TEST(UniquePointerTests, canBeMoved) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2;
    ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), (void *) NULL);
}

TEST(UniquePointerTests, canBeConstructedByMoving) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2(move(ptr1));
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), (void *) NULL);
}

TEST(UniquePointerTests, canBeCastedToRawPointer) {
    auto ptr = make_unique(10);
    int *rawPtr = ptr;
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(*rawPtr, 10);
    EXPECT_EQ(ptr.get(), rawPtr);
}

TEST(UniquePointerTests, canHaveItsValueModified) {
    auto ptr = make_unique(10);
    *ptr = 39;
    EXPECT_EQ(*ptr, 39);
}

