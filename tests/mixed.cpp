#include <list.hpp>
#include <unique_ptr.hpp>
#include <shared_ptr.hpp>
#include <algorithm.hpp>
#include <string.hpp>
#include <array.hpp>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(mixed, can_create_shared_pointer_list) {
    list<shared_ptr<int>> list;
    auto ptr1 = make_shared<int>(5);
    list.push_front(ptr1);
    list.push_front(shared_ptr<int>(new int(6)));
    auto it = list.begin();
    REQUIRE_EQ(**it, 6);
    REQUIRE(it->get_ref_count() == 1);
    it++;
    REQUIRE_EQ(**it, 5);
    REQUIRE(it->get_ref_count() == 2);
}

TEST(mixed, can_use_for_each_on_list) {
    list<int> list;
    int result[3];
    list.push_front(3);
    list.push_front(5);
    list.push_front(78);
    int i = 0;
    for_each(list, [&](int &e) { result[i++] = e; });
    REQUIRE_EQ(result[0], 78);
    REQUIRE_EQ(result[1], 5);
    REQUIRE_EQ(result[2], 3);
    REQUIRE_EQ(count(list, 78), 1);
    for_each(list.begin(), list.end(), [](int &e) { e = 22; });
    i = 0;
    for_each(list, [&](int &e) { result[i++] = e; });
    REQUIRE_EQ(result[0], 22);
    REQUIRE_EQ(result[1], 22);
    REQUIRE_EQ(result[2], 22);
}

TEST(mixed, can_use_count_on_list) {
    list<int> list{3, 7, 8, 6, 5, 3, 7, 9, 60, 55, 8, 6};
    REQUIRE_EQ(count(list, 3), 2);
    REQUIRE_EQ(count(list, 9), 1);
    REQUIRE_EQ(count(list, 20), 0);
    auto result1 = count_if(list, [](const int &e) { return e > 3; });
    REQUIRE_EQ(result1, 10);
    auto result2 = count_if(list, [](const int &e) { return e < 3; });
    REQUIRE_EQ(result2, 0);
    auto result3 = count_if(list, [](const int &) {
        return 1;
    });
    REQUIRE_EQ(result3, 12);
    auto result4 = count_if(list, [](const int &) {
        return 0;
    });
    REQUIRE_EQ(result4, 0);
}

TEST(mixed, can_swap_same_size_lists) {
    list<int> list1{3, 7, 8, 6};
    list<int> list2{9, 15, -3, 21};
    swap(list1, list2);
    REQUIRE(list1.size() ==  4);
    REQUIRE_EQ(list1.front(), 9);
    REQUIRE_EQ(list1.back(), 21);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list2.front(), 3);
    REQUIRE_EQ(list2.back(), 6);
    swap(list1, list2);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list2.front(), 9);
    REQUIRE_EQ(list2.back(), 21);
    REQUIRE(list1.size() == 4);
    REQUIRE_EQ(list1.front(), 3);
    REQUIRE_EQ(list1.back(), 6);
}

TEST(mixed, can_swap_different_size_lists) {
    list<int> list1{3, 7, 8, 6, 8, 4};
    list<int> list2{9, 15, -3, 21};
    swap(list1, list2);
    REQUIRE(list1.size() == 4);
    REQUIRE_EQ(list1.front(), 9);
    REQUIRE_EQ(list1.back(), 21);
    REQUIRE(list2.size() == 6);
    REQUIRE_EQ(list2.front(), 3);
    REQUIRE_EQ(list2.back(), 4);
    swap(list1, list2);
    REQUIRE(list2.size() == 4);
    REQUIRE_EQ(list2.front(), 9);
    REQUIRE_EQ(list2.back(), 21);
    REQUIRE(list1.size() == 6);
    REQUIRE_EQ(list1.front(), 3);
    REQUIRE_EQ(list1.back(), 4);
}

TEST(mixed, can_fill_list) {
    {
        list<int> list;
        list.resize(30);
        fill(list, 945);
        REQUIRE(list.size() == 30);
        REQUIRE_EQ(list.front(), 945);
        REQUIRE_EQ(list.back(), 945);
        list.resize(10);
        fill(list, 3);
        REQUIRE(list.size() == 10);
        REQUIRE_EQ(list.front(), 3);
        REQUIRE_EQ(list.back(), 3);
    }
    {
        list<char> list;
        list.resize(100);
        fill(list.begin(), list.end(), 43);
        for (auto it = list.begin(); it != list.end(); ++it) {
            REQUIRE_EQ(*it, 43);
        }
    }
    {
        array<unsigned, 10> array;
        fill(array.begin(), 10, 21);
        for (auto it = array.begin(); it != array.end(); ++it) {
            REQUIRE_EQ(*it, 21u);
        }
    }
}

TEST(mixed, can_find_first_occurrence_in_array) {
    array<char, 4> string{'t', 'e', 's', 't'};
    REQUIRE(first_occurrence(string, 't') == cbegin(string));
    REQUIRE(first_occurrence(string, 'e') == cbegin(string) + 1);
    REQUIRE(first_occurrence(string, 'a') == cend(string));
    REQUIRE(first_occurrence(string.cbegin(), string.cend(), 't') == string.cbegin());
    REQUIRE(first_occurrence(string.begin(), string.end(), 't') == string.begin());
    REQUIRE(first_occurrence(string.begin(), string.begin() + 2, 't') == string.begin());
    REQUIRE(first_occurrence(string.begin(), string.begin() + 2, 'e') == string.begin() + 1);
    REQUIRE(first_occurrence(string.begin(), string.begin() + 2, 'z') == string.begin() + 2);
}

TEST(mixed, can_find_last_occurrence_in_array) {
    array<char, 4> string{'t', 'e', 's', 't'};
    REQUIRE(last_occurrence(string, 't') == cend(string) - 1);
    REQUIRE(*last_occurrence(string, 't') == 't');
    REQUIRE(last_occurrence(string, 'e') == cbegin(string) + 1);
    REQUIRE(last_occurrence(string, 'a') == cend(string));
    REQUIRE(last_occurrence(string.cbegin(), string.cend(), 't') == string.cend() - 1);
    REQUIRE(last_occurrence(string.begin(), string.end(), 't') == string.end() - 1);
    REQUIRE(last_occurrence(string.begin(), string.begin() + 2, 't') == string.begin());
    REQUIRE(last_occurrence(string.begin(), string.begin() + 2, 'e') == string.begin() + 1);
    REQUIRE(last_occurrence(string.begin(), string.begin() + 2, 'z') == string.begin() + 2);
}

TEST(mixed, can_copy_from_list_to_array) {
    list<int> list{1, 2, 4, 6, 8};
    array<int, 5> array;
    copy(list.begin(), list.end(), array.begin(), array.end());
    REQUIRE_EQ(*list.begin(), 1);
    REQUIRE_EQ(*--list.end(), 8);
    auto it = array.begin();
    REQUIRE_EQ(*it++, 1);
    REQUIRE_EQ(*it++, 2);
    REQUIRE_EQ(*it++, 4);
    REQUIRE_EQ(*it++, 6);
    REQUIRE_EQ(*it++, 8);
}

TEST(mixed, iterators_on_carrays_work) {
    int data[] = {2, 4, 6, 10, 210, 4345};
    auto it = begin(data);
    REQUIRE_EQ(*it, 2);
    it = end(data);
    REQUIRE_EQ(it - begin(data), 6u);
    auto const_it = cbegin(data);
    REQUIRE_EQ(*const_it, 2);
    const_it = cend(data);
    REQUIRE_EQ(const_it - cbegin(data), 6u);
}

