//
// Created by maciek on 13.06.16.
//

#include <gtest/gtest.h>
#include <Array.h>

TEST(ArrayTests, canCreateEmptyString)
{
    Array<int, 0> array;
    unsigned result = array.size();
    EXPECT_EQ(result, 0);
}

TEST(ArrayTests, canCreateInitializedArray)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    EXPECT_EQ(array[0], 2);
    EXPECT_EQ(array[4], 6);
    EXPECT_EQ(array.size(), 5);
}

TEST(ArrayTests, canReadElementsSequentially)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    int cArray[5] = { 0, 0, 0, 0, 0 };
    unsigned i = 0;
    for (const auto &elem : array)
        cArray[i++] = elem;
    EXPECT_EQ(cArray[0], 2);
    EXPECT_EQ(cArray[2], 4);
    EXPECT_EQ(cArray[4], 6);
}

TEST(ArrayTests, canModifyElementsSequentially)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    unsigned i = 10;
    for (auto &elem : array)
        elem = i++;
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[2], 12);
    EXPECT_EQ(array[4], 14);
}

TEST(ArrayTests, canModify)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    array[0] = 10;
    array[1] = 11;
    array[4] = 14;
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 11);
    EXPECT_EQ(array[4], 14);
}

TEST(ArrayTests, canIncrementIterator)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    auto it = array.begin();
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
}

TEST(ArrayTests, canDecrementIterator)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    auto it = array.end();
    it--;
    EXPECT_EQ(*it, 6);
    --it;
    EXPECT_EQ(*it, 5);
}

TEST(ArrayTests, canIncrementAndDecrementIterator)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    auto it = array.begin();
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    it--;
    EXPECT_EQ(*it, 2);
}

TEST(ArrayTests, canCompareIterators)
{
    Array<int, 5> array{ 2, 3, 4, 5, 6 };
    auto it1 = array.begin();
    auto it2 = array.begin();
    EXPECT_EQ(it1 == it2, true);
    it1++;
    EXPECT_EQ(it1 != it2, true);
}

