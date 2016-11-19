#include <gtest/gtest.h>
#include <array.h>

using namespace yacppl;

TEST(ArrayTests, canCreateEmptyString) {
    array<int, 0> array;
    unsigned result = array.size();
    EXPECT_TRUE(result == 0);
}

TEST(ArrayTests, canCreateInitializedArray) {
    array<int, 5> array{2, 3, 4, 5, 6};
    EXPECT_EQ(array[0], 2);
    EXPECT_EQ(array[4], 6);
    EXPECT_TRUE(array.size() == 5);
}

TEST(ArrayTests, canReadElementsSequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    int cArray[5] = {0, 0, 0, 0, 0};
    unsigned i = 0;
    for (const auto &elem : array)
        cArray[i++] = elem;
    EXPECT_EQ(cArray[0], 2);
    EXPECT_EQ(cArray[2], 4);
    EXPECT_EQ(cArray[4], 6);
}

TEST(ArrayTests, canModifyElementsSequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    unsigned i = 10;
    for (auto &elem : array)
        elem = i++;
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[2], 12);
    EXPECT_EQ(array[4], 14);
}

TEST(ArrayTests, canModify) {
    array<int, 5> array{2, 3, 4, 5, 6};
    array[0] = 10;
    array[1] = 11;
    array[4] = 14;
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 11);
    EXPECT_EQ(array[4], 14);
}

TEST(ArrayTests, canIncrementIterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
}

TEST(ArrayTests, canDecrementIterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.end();
    it--;
    EXPECT_EQ(*it, 6);
    --it;
    EXPECT_EQ(*it, 5);
}

TEST(ArrayTests, canIncrementAndDecrementIterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    it--;
    EXPECT_EQ(*it, 2);
}

TEST(ArrayTests, canCompareIterators) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it1 = array.begin();
    auto it2 = array.begin();
    EXPECT_EQ(it1 == it2, true);
    it1++;
    EXPECT_EQ(it1 != it2, true);
}

