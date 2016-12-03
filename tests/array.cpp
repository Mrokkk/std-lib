#include <array.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(array, can_be_empty) {
    array<int, 0> array;
    unsigned result = array.size();
    REQUIRE(result == 0);
    REQUIRE(array.end() - array.begin() == 0);
}

TEST(array, can_be_initialized) {
    array<int, 5> array{2, 3, 4, 5, 6};
    REQUIRE(array[0] == 2);
    REQUIRE(array[4] == 6);
    REQUIRE(array.size() == 5);
    REQUIRE(array.end() - array.begin() == 5);
}

TEST(array, can_read_elements_sequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    int c_array[5] = {0, 0, 0, 0, 0};
    unsigned i = 0;
    for (const auto &elem : array)
        c_array[i++] = elem;
    REQUIRE(c_array[0] == 2);
    REQUIRE(c_array[2] == 4);
    REQUIRE(c_array[4] == 6);
}

TEST(array, can_modify_elements_sequentially) {
    array<int, 5> array{2, 3, 4, 5, 6};
    unsigned i = 10;
    for (auto &elem : array)
        elem = i++;
    REQUIRE(array[0] == 10);
    REQUIRE(array[2] == 12);
    REQUIRE(array[4] == 14);
}

TEST(array, can_be_modified_using_brackets) {
    array<int, 5> array{2, 3, 4, 5, 6};
    array[0] = 10;
    array[1] = 11;
    array[4] = 14;
    REQUIRE(array[0] == 10);
    REQUIRE(array[1] == 11);
    REQUIRE(array[4] == 14);
}

TEST(array, can_increment_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    REQUIRE(*it == 2);
    it++;
    REQUIRE(*it == 3);
    ++it;
    REQUIRE(*it == 4);
}

TEST(array, can_decrement_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.end();
    it--;
    REQUIRE(*it == 6);
    --it;
    REQUIRE(*it == 5);
}

TEST(array, can_increment_and_decrement_iterator) {
    array<int, 5> array{2, 3, 4, 5, 6};
    auto it = array.begin();
    REQUIRE(*it == 2);
    it++;
    REQUIRE(*it == 3);
    it--;
    REQUIRE(*it == 2);
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
    REQUIRE(2 == array2[0]);
    auto it = array2.begin();
    REQUIRE(array2.end() - it == 5);
    ++it;
    REQUIRE(array2.end() - it == 4);
    it++;
    REQUIRE(array2.end() - it == 3);
}

