#include <gtest/gtest.h>
#include <pointer.h>
#include <move.h>

using namespace yacppl;

TEST(SharedPointerTests, canCreateEmptyPointer) {
    shared_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.get_ref_count(), 0);
}

TEST(SharedPointerTests, canCreateValidPointer) {
    shared_ptr<int> ptr(new int(4));
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(SharedPointerTests, canBeDerefereced) {
    shared_ptr<int> ptr(new int(4));
    EXPECT_EQ(*ptr, 4);
}

TEST(SharedPointerTests, canBeAssigned) {
    shared_ptr<int> ptr;
    ptr = make_shared<int>(5);
    EXPECT_EQ(*ptr, 5);
}

TEST(SharedPointerTests, canBeCopied) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2;
    ptr2 = ptr1;
    EXPECT_EQ(*ptr1, 10);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get_ref_count(), 2);
    EXPECT_EQ(ptr2.get_ref_count(), 2);
    EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeMoved) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2;
    ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.get_ref_count(), 0);
    EXPECT_EQ(ptr2.get_ref_count(), 1);
    EXPECT_NE(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeConstructedByCopy) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2(ptr1);
    EXPECT_EQ(*ptr1, 10);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get_ref_count(), 2);
    EXPECT_EQ(ptr2.get_ref_count(), 2);
    EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeConstructedByMoving) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.get_ref_count(), 0);
    EXPECT_EQ(ptr2.get_ref_count(), 1);
    EXPECT_NE(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeCastedToRawPointer) {
    auto ptr = make_shared<int>(10);
    int *rawPtr = ptr;
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(*rawPtr, 10);
    EXPECT_EQ(ptr.get(), rawPtr);
}

TEST(SharedPointerTests, canHaveItsValueModified) {
    auto ptr = make_shared(10);
    *ptr = 39;
    EXPECT_EQ(*ptr, 39);
    EXPECT_EQ(ptr.get_ref_count(), 1);
}
