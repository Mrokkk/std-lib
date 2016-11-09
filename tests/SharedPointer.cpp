#include <gtest/gtest.h>
#include <Pointer.h>
#include <Move.h>

TEST(SharedPointerTests, canCreateEmptyPointer) {
    SharedPointer<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.getRefCount(), 0);
}

TEST(SharedPointerTests, canCreateValidPointer) {
    SharedPointer<int> ptr(new int(4));
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(SharedPointerTests, canBeDerefereced) {
    SharedPointer<int> ptr(new int(4));
    EXPECT_EQ(*ptr, 4);
}

TEST(SharedPointerTests, canBeAssigned) {
    SharedPointer<int> ptr;
    ptr = makeShared<int>(5);
    EXPECT_EQ(*ptr, 5);
}

TEST(SharedPointerTests, canBeCopied) {
    auto ptr1 = makeShared<int>(10);
    SharedPointer<int> ptr2;
    ptr2 = ptr1;
    EXPECT_EQ(*ptr1, 10);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.getRefCount(), 2);
    EXPECT_EQ(ptr2.getRefCount(), 2);
    EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeMoved) {
    auto ptr1 = makeShared<int>(10);
    SharedPointer<int> ptr2;
    ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.getRefCount(), 0);
    EXPECT_EQ(ptr2.getRefCount(), 1);
    EXPECT_NE(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeConstructedByCopy) {
    auto ptr1 = makeShared<int>(10);
    SharedPointer<int> ptr2(ptr1);
    EXPECT_EQ(*ptr1, 10);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.getRefCount(), 2);
    EXPECT_EQ(ptr2.getRefCount(), 2);
    EXPECT_EQ(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeConstructedByMoving) {
    auto ptr1 = makeShared<int>(10);
    SharedPointer<int> ptr2 = move(ptr1);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.getRefCount(), 0);
    EXPECT_EQ(ptr2.getRefCount(), 1);
    EXPECT_NE(ptr1.get(), ptr2.get());
}

TEST(SharedPointerTests, canBeCastedToRawPointer) {
    auto ptr = makeShared<int>(10);
    int *rawPtr = ptr;
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(*rawPtr, 10);
    EXPECT_EQ(ptr.get(), rawPtr);
}

TEST(SharedPointerTests, canHaveItsValueModified) {
    auto ptr = makeShared(10);
    *ptr = 39;
    EXPECT_EQ(*ptr, 39);
    EXPECT_EQ(ptr.getRefCount(), 1);
}
