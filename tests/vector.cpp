#include <vector.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(vector, can_be_created) {
    vector<int> v;
    REQUIRE(v.empty());
    REQUIRE_EQ(v.size(), 0u);
    REQUIRE(v.begin() == nullptr);
    REQUIRE(v.end() == nullptr);
}

TEST(vector, can_be_created_from_initializer_list) {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    REQUIRE_FALSE(v.empty());
    REQUIRE_EQ(v.size(), 7u);
    REQUIRE_EQ(v[0], 1);
    REQUIRE_EQ(v[1], 2);
    REQUIRE_EQ(v[2], 3);
    REQUIRE_EQ(v[3], 4);
    REQUIRE_EQ(v[4], 5);
    REQUIRE_EQ(v[5], 6);
    REQUIRE_EQ(v[6], 7);
}

TEST(vector, can_be_created_from_other_vector) {
    vector<int> v1{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> v2(v1);
    REQUIRE_FALSE(v2.empty());
    REQUIRE_EQ(v2.size(), 10u);
}

TEST(vector, can_push_back_element) {
    vector<int> v;
    v.push_back(-934);
    REQUIRE_FALSE(v.empty());
    REQUIRE_EQ(v.size(), 1u);
    REQUIRE_EQ(v.front(), -934);
    REQUIRE_EQ(v.back(), -934);
    v.push_back(2938);
    REQUIRE_FALSE(v.empty());
    REQUIRE_EQ(v.size(), 2u);
    REQUIRE_EQ(v.front(), -934);
    REQUIRE_EQ(v.back(), 2938);
    v.push_back(932448);
    REQUIRE_FALSE(v.empty());
    REQUIRE_EQ(v.size(), 3u);
    REQUIRE_EQ(v.front(), -934);
    REQUIRE_EQ(v.back(), 932448);
}

TEST(vector, can_iterate) {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    auto it = v.begin();
    REQUIRE(it != nullptr);
    REQUIRE_EQ(*it++, 1);
    REQUIRE_EQ(*it++, 2);
    REQUIRE_EQ(*it++, 3);
    REQUIRE_EQ(*it++, 4);
    REQUIRE_EQ(*it++, 5);
    it = v.end();
    *--it;
    REQUIRE_EQ(*it--, 7);
    REQUIRE_EQ(*it--, 6);
    REQUIRE_EQ(*it--, 5);
    REQUIRE_EQ(*it--, 4);
    REQUIRE_EQ(*it--, 3);
}

TEST(vector, const_iterator_works) {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    auto const_it = v.cbegin();
    REQUIRE_FALSE(const_it == v.end());
    const_it++;
    REQUIRE_EQ(*const_it, 2);
    const_it = v.end();
    const_it--;
    REQUIRE_EQ(*const_it, 7);
    const_it = v.cend();
    REQUIRE_EQ(*--const_it, 7);
}

template <typename Type>
void check_const_vector(const vector<Type> &v, unsigned expected_size) {
    auto size = 0u;
    for (const auto &e : v) {
        (void)e;
        size++;
    }
    REQUIRE_EQ(size, expected_size);
}

TEST(vector, range_based_for_works) {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    int i = 0;
    auto size = 0u;
    for (const auto &e : v) {
        REQUIRE_EQ(e, i);
        ++size;
        ++i;
    }
    REQUIRE_EQ(size, 8u);
    i = 0;
    size = 0u;
    for (auto &e : v) {
        REQUIRE_EQ(e, i);
        ++size;
        ++i;
    }
    REQUIRE_EQ(size, 8u);
    check_const_vector(v, 8u);
}

