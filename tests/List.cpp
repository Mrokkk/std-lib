//
// Created by maciek on 13.06.16.
//

#include <gtest/gtest.h>
#include <List.h>
#include <Move.h>

TEST(ListTests, canCreateEmptyList)
{
    List<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTests, canAddFrontItem)
{
    List<int> list;
    list.push_front(2);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 2);
}

TEST(ListTests, canAddTwoFrontItems)
{
    List<int> list;
    list.push_front(2);
    list.push_front(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(ListTests, canAddBackItem)
{
    List<int> list;
    list.push_back(4);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 4);
}

TEST(ListTests, canAddBackTwoItems)
{
    List<int> list;
    list.push_back(8);
    list.push_back(3);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 8);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTests, canBeInitializedWithInitializerList)
{
    List<int> list{ 2, 5, 6, 88, 4 };
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 4);
    int result[5];
    int i = 0;
    for (auto &it : list)
        result[i++] = it;
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 6);
    EXPECT_EQ(result[3], 88);
    EXPECT_EQ(result[4], 4);
}

TEST(ListTests, canAccessElements)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    int result[3];
    int i = 0;
    for (const auto &it : list)
        result[i++] = it;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(ListTests, canPopBack)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    EXPECT_EQ(list.front(), 1);
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.front(), 1);
}

TEST(ListTests, canPopFront)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    EXPECT_EQ(list.front(), 10);
    list.pop_front();
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.front(), 1);
}

TEST(ListTests, canBeResized)
{
    List<int> list;
    list.resize(20);
    EXPECT_EQ(list.size(), 20);
    for (auto &it : list)
        it = 38;
    EXPECT_EQ(list.front(), 38);
    EXPECT_EQ(list.back(), 38);
    list.resize(2);
    EXPECT_EQ(list.front(), 38);
    EXPECT_EQ(list.back(), 38);
    EXPECT_EQ(list.size(), 2);
}

TEST(ListTests, canIncrementIterator)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    it = list.begin();
    *it = 34;
    EXPECT_EQ(*it, 34);
    EXPECT_EQ(list.front(), 34);
}

TEST(ListTests, canDecrementIterator)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.end();
    it--;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTests, canIncrementAndDecrementIterator)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 1);
    it--;
    EXPECT_EQ(*it, 10);
}

TEST(ListTests, canCompareIterators)
{
    List<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it1 = list.begin();
    auto it2 = it1;
    EXPECT_EQ(it1 == it2, true);
    it2++;
    EXPECT_EQ(it1 != it2, true);
}

TEST(ListTests, canBeConstructedByCopy)
{
    List<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    List<int> list2(list1);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list2.front(), 10);
    EXPECT_EQ(list2.back(), 3);
}

TEST(ListTests, canBeAssigned)
{
    List<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    List<int> list2;
    list2.push_back(99);
    list2.push_back(120);
    list2 = list1;
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list1.front(), 10);
    EXPECT_EQ(list2.front(), 10);
    EXPECT_EQ(list2.back(), 3);
}

TEST(ListTests, canBeConstructedByMove)
{
    List<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    List<int> list2(move(list1));
    int result[4];
    int i = 0;
    for (const auto &it : list2)
        result[i++] = it;
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 10);
    EXPECT_EQ(list2.back(), 3);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}

TEST(ListTests, canBeMoved)
{
    List<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    List<int> list2;
    list2.push_back(4);
    list2.push_back(54);
    list2 = move(list1);
    int result[4];
    int i = 0;
    for (const auto &it : list2)
        result[i++] = it;
    EXPECT_EQ(list1.size(), 0);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 10);
    EXPECT_EQ(list2.back(), 3);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}

TEST(ListTests, canEraseSingleElement)
{
    List<int> list;
    list.push_front(43);
    list.push_front(-59);
    list.push_back(23);
    auto it = list.begin();
    ++it;
    EXPECT_EQ(list.front(), -59);
    EXPECT_EQ(list.back(), 23);
    list.erase(it);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), -59);
    EXPECT_EQ(list.back(), 23);
    list.erase(list.begin());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 23);
    EXPECT_EQ(list.back(), 23);
    list.erase(list.end()--);
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTests, canEraseElements)
{
    List<int> list;
    list.push_front(43);
    list.push_front(-59);
    list.push_back(23);
    list.push_back(13);
    list.erase(++list.begin(), list.end());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), -59);
    EXPECT_EQ(list.back(), -59);
    list.erase(list.begin(), list.end());
    EXPECT_EQ(list.size(), 0);
}
