#include <array.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(array, can_create_empty_string) {
    array<int, 0> array;
    unsigned result = array.size();
    REQUIRE(result == 0);
    REQUIRE(array.end() - array.begin() == 0);
}

TEST(array, can_create_initialized_array) {
    array<int, 5> array{2, 3, 4, 5, 6};
    REQUIRE_EQ(array[0], 2);
    REQUIRE_EQ(array[4], 6);
    REQUIRE(array.size() == 5);
    REQUIRE(array.end() - array.begin() == 5);
}

TEST(array, can_read_elements_sequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    int c_array[5] = {0, 0, 0, 0, 0};
    unsigned i = 0;
    for (const auto &elem : array)
        c_array[i++] = elem;
    REQUIRE_EQ(c_array[0], 2);
    REQUIRE_EQ(c_array[2], 4);
    REQUIRE_EQ(c_array[4], 6);
}

TEST(array, can_modify_elements_sequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    unsigned i = 10;
    for (auto &elem : array)
        elem = i++;
    REQUIRE_EQ(array[0], 10);
    REQUIRE_EQ(array[2], 12);
    REQUIRE_EQ(array[4], 14);
}

TEST(array, can_modify) {
    array<int, 5> array{2, 3, 4, 5, 6};
    array[0] = 10;
    array[1] = 11;
    array[4] = 14;
    REQUIRE_EQ(array[0], 10);
    REQUIRE_EQ(array[1], 11);
    REQUIRE_EQ(array[4], 14);
}

TEST(array, can_increment_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    REQUIRE_EQ(*it, 2);
    it++;
    REQUIRE_EQ(*it, 3);
    ++it;
    REQUIRE_EQ(*it, 4);
}

TEST(array, can_decrement_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.end();
    it--;
    REQUIRE_EQ(*it, 6);
    --it;
    REQUIRE_EQ(*it, 5);
}

TEST(array, can_increment_and_decrement_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    REQUIRE_EQ(*it, 2);
    it++;
    REQUIRE_EQ(*it, 3);
    it--;
    REQUIRE_EQ(*it, 2);
}

TEST(array, can_compare_iterators) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it1 = array.begin();
    auto it2 = array.begin();
    REQUIRE(it1 == it2);
    it1++;
    REQUIRE(it1 != it2);
}

TEST(array, can_be_copied) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto array2 = array;
    REQUIRE_EQ(2, array2[0]);
    auto it = array2.begin();
    REQUIRE(array2.end() - it == 5);
    ++it;
    REQUIRE(array2.end() - it == 4);
    it++;
    REQUIRE(array2.end() - it == 3);
}

TEST(array, const_iterator_works) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.cbegin();
    REQUIRE_EQ(*it, 2);
    auto it2 = ++it;
    REQUIRE_EQ(*it2, 3);
    REQUIRE_EQ(*it, 3);
    --it;
    REQUIRE_EQ(*it, 2);
    it2++;
    REQUIRE_EQ(*it2, 4);
    it = array.end();
    --it;
    REQUIRE_EQ(*it.get(), 6);
}

TEST(array, nonconst_iterator_works) {
    array<int, 5>::iterator it;
    array<int, 5> array{2, 3, 4, 5, 6};
    it = array.begin();
    REQUIRE_EQ(*it, 2);
    *it = 1;
    REQUIRE_EQ(*it, 1);
    auto it2 = ++it;
    REQUIRE_EQ(*it2, 3);
    REQUIRE_EQ(*it, 3);
    --it;
    REQUIRE_EQ(*it, 1);
    it2++;
    REQUIRE_EQ(*it2, 4);
    it = array.end();
    --it;
    REQUIRE_EQ(*it.get(), 6);
}

void check_const_array(const array<int, 5> &array) {
    auto size = 0u;
    for (const auto &i : array) {
        size++;
        REQUIRE_EQ(i, 3);
    }
}

TEST(array, range_based_for_works) {
    array<int, 5> array{2, 3, 4, 5, 6};
    size_t size = 0;
    for (auto &i : array) {
        size++;
        i = 3;
    }
    REQUIRE_EQ(size, 5u);
    size = 0u;
    for (const auto &i : array) {
        size++;
        REQUIRE_EQ(i, 3);
    }
    REQUIRE_EQ(size, 5u);
}

