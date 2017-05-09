#include <array.hpp>
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

TEST(array, can_modify) {
    array<int, 5> array{2, 3, 4, 5, 6};
    array[0] = 10;
    array[1] = 11;
    array[4] = 14;
    REQUIRE_EQ(array[0], 10);
    REQUIRE_EQ(array[1], 11);
    REQUIRE_EQ(array[4], 14);
}

TEST(array, can_access_underlying_data) {
    array<int, 5> array{2, 12149, -3293, 4340, -1};
    auto data = array.data();
    REQUIRE(data);
    REQUIRE_EQ(*data, 2);
    REQUIRE_EQ(data[4], -1);
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
    array<int, 5> array1{2, 3, 4, 5, 6};
    auto it = array1.cbegin();
    REQUIRE_EQ(*it, 2);
    auto it2 = ++it;
    REQUIRE_EQ(*it2, 3);
    REQUIRE_EQ(*it, 3);
    --it;
    REQUIRE_EQ(*it, 2);
    it2++;
    REQUIRE_EQ(*it2, 4);
    it = array1.cend();
    --it;
    REQUIRE_EQ(*it, 6);
    array<int, 5>::const_iterator const_it(array1.begin());
    REQUIRE_EQ(*const_it, 2);
    const_it = array1.end();
    const_it--;
    REQUIRE_EQ(*const_it, 6);
    const_it = nullptr;
    const_it = array1.cbegin();
    REQUIRE_EQ(*const_it, 2);
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
    REQUIRE_EQ(*it, 6);
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
    check_const_array(array);
}

#include "list.hpp"

namespace {

template <typename Container, typename Type>
void check_container() {
    Container c{1, 2, 4, 7, 9};
    array<Type, 5> a(c);
    REQUIRE_EQ(a[0], 1);
    REQUIRE_EQ(a[1], 2);
    REQUIRE_EQ(a[2], 4);
    REQUIRE_EQ(a[3], 7);
    REQUIRE_EQ(a[4], 9);
}

} // namespace

TEST(array, can_be_created_from_other_containers) {
    check_container<list<int>, int>();
}

