#include <list.h>
#include <move.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(list, can_create_empty_list) {
    list<int> list;
    REQUIRE(list.size() == 0);
}

TEST(list, can_add_front_item) {
    list<int> list;
    list.push_front(2);
    REQUIRE(list.size() == 1);
    REQUIRE_EQ(list.front(), 2);
}

TEST(list, can_add_two_front_items) {
    list<int> list;
    list.push_front(2);
    list.push_front(1);
    REQUIRE(list.size() == 2);
    REQUIRE_EQ(list.front(), 1);
    REQUIRE_EQ(list.back(), 2);
}

TEST(list, can_add_back_item) {
    list<int> list;
    list.push_back(4);
    REQUIRE(list.size() == 1);
    REQUIRE_EQ(list.back(), 4);
}

TEST(list, can_add_back_two_items) {
    list<int> list;
    list.push_back(8);
    list.push_back(3);
    REQUIRE(list.size() == 2);
    REQUIRE_EQ(list.front(), 8);
    REQUIRE_EQ(list.back(), 3);
}

TEST(list, can_be_initialized_with_initializer_list) {
    list<int> list{2, 5, 6, 88, 4};
    REQUIRE(list.size() == 5);
    REQUIRE_EQ(list.front(), 2);
    REQUIRE_EQ(list.back(), 4);
    int result[5];
    int i = 0;
    for (auto &it : list)
        result[i++] = it;
    REQUIRE_EQ(result[0], 2);
    REQUIRE_EQ(result[1], 5);
    REQUIRE_EQ(result[2], 6);
    REQUIRE_EQ(result[3], 88);
    REQUIRE_EQ(result[4], 4);
}

TEST(list, can_access_elements) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    int result[3];
    int i = 0;
    for (const auto &it : list)
        result[i++] = it;
    REQUIRE_EQ(result[0], 1);
    REQUIRE_EQ(result[1], 2);
    REQUIRE_EQ(result[2], 3);
}

TEST(list, can_pop_back) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    REQUIRE_EQ(list.front(), 1);
    list.pop_back();
    REQUIRE(list.size() == 2);
    REQUIRE_EQ(list.back(), 2);
    REQUIRE_EQ(list.front(), 1);
}

TEST(list, can_pop_front) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    REQUIRE_EQ(list.front(), 10);
    list.pop_front();
    REQUIRE(list.size() == 3);
    REQUIRE_EQ(list.back(), 3);
    REQUIRE_EQ(list.front(), 1);
}

TEST(list, can_be_resized) {
    list<int> list;
    list.resize(20);
    REQUIRE(list.size() == 20);
    for (auto &it : list)
        it = 38;
    REQUIRE_EQ(list.front(), 38);
    REQUIRE_EQ(list.back(), 38);
    list.resize(2);
    REQUIRE_EQ(list.front(), 38);
    REQUIRE_EQ(list.back(), 38);
    REQUIRE(list.size() == 2);
}

TEST(list, can_increment_iterator) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.begin();
    REQUIRE_EQ(*it, 10);
    it++;
    REQUIRE_EQ(*it, 1);
    ++it;
    REQUIRE_EQ(*it, 2);
    it = list.begin();
    *it = 34;
    REQUIRE_EQ(*it, 34);
    REQUIRE_EQ(list.front(), 34);
}

TEST(list, can_decrement_iterator) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.end();
    it--;
    REQUIRE_EQ(*it, 3);
    --it;
    REQUIRE_EQ(*it, 2);
}

TEST(list, can_increment_and_decrement_iterator) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it = list.begin();
    REQUIRE_EQ(*it, 10);
    it++;
    REQUIRE_EQ(*it, 1);
    it--;
    REQUIRE_EQ(*it, 10);
}

TEST(list, can_compare_iterators) {
    list<int> list;
    list.push_back(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(10);
    auto it1 = list.begin();
    auto it2 = it1;
    REQUIRE_EQ(it1 == it2, true);
    it2++;
    REQUIRE_EQ(it1 != it2, true);
}

TEST(list, can_be_constructed_by_copy) {
    list<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    list<int> list2(list1);
    REQUIRE_EQ(list1.front(), 10);
    REQUIRE_EQ(list2.front(), 10);
    REQUIRE_EQ(list2.back(), 3);
}

TEST(list, can_be_assigned) {
    list<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    list<int> list2;
    list2.push_back(99);
    list2.push_back(120);
    list2 = list1;
    REQUIRE(list1.size() == 4);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list1.front(), 10);
    REQUIRE_EQ(list2.front(), 10);
    REQUIRE_EQ(list2.back(), 3);
}

TEST(list, can_be_constructed_by_move) {
    list<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    list<int> list2(move(list1));
    int result[4];
    int i = 0;
    for (const auto &it : list2)
        result[i++] = it;
    REQUIRE(list1.size() == 0);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list2.front(), 10);
    REQUIRE_EQ(list2.back(), 3);
    REQUIRE_EQ(result[0], 10);
    REQUIRE_EQ(result[1], 1);
    REQUIRE_EQ(result[2], 2);
    REQUIRE_EQ(result[3], 3);
}

TEST(list, can_be_moved) {
    list<int> list1;
    list1.push_back(3);
    list1.push_front(2);
    list1.push_front(1);
    list1.push_front(10);
    list<int> list2;
    list2.push_back(4);
    list2.push_back(54);
    list2 = move(list1);
    int result[4];
    int i = 0;
    for (const auto &it : list2)
        result[i++] = it;
    REQUIRE(list1.size() == 0);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list2.front(), 10);
    REQUIRE_EQ(list2.back(), 3);
    REQUIRE_EQ(result[0], 10);
    REQUIRE_EQ(result[1], 1);
    REQUIRE_EQ(result[2], 2);
    REQUIRE_EQ(result[3], 3);
}

TEST(list, can_erase_single_element) {
    list<int> list;
    list.push_front(43);
    list.push_front(-59);
    list.push_back(23);
    auto it = list.begin();
    ++it;
    REQUIRE_EQ(list.front(), -59);
    REQUIRE_EQ(list.back(), 23);
    list.erase(it);
    REQUIRE(list.size() == 2);
    REQUIRE_EQ(list.front(), -59);
    REQUIRE_EQ(list.back(), 23);
    list.erase(list.begin());
    REQUIRE(list.size() == 1);
    REQUIRE_EQ(list.front(), 23);
    REQUIRE_EQ(list.back(), 23);
    list.erase(--list.end());
    REQUIRE(list.size() == 0);
}

TEST(list, can_erase_elements) {
    list<int> list;
    list.push_front(43);
    list.push_front(-59);
    list.push_back(23);
    list.push_back(13);
    list.erase(++list.begin(), list.end());
    REQUIRE(list.size() == 1);
    REQUIRE_EQ(list.front(), -59);
    REQUIRE_EQ(list.back(), -59);
    list.erase(list.begin(), list.end());
    REQUIRE(list.size() == 0);
}

