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

TEST(vector, can_be_created_by_move) {
    vector<int> v1{1, 2, 3, 4, 5, 6};
    vector<int> v2(move(v1));
    REQUIRE_EQ(v1.size(), 0u);
    REQUIRE(v1.empty());
    REQUIRE_EQ(v2.size(), 6u);
    REQUIRE_EQ(v2[0], 1);
    REQUIRE_EQ(v2[3], 4);
    REQUIRE_EQ(v2[5], 6);
    vector<int> v3;
    vector<int> v4(move(v3));
    REQUIRE_EQ(v4.size(), 0u);
}

TEST(vector, can_be_created_by_copy) {
    vector<int> v1{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> v2(v1);
    REQUIRE_FALSE(v2.empty());
    REQUIRE_EQ(v2.size(), 10u);
    vector<int> v3;
    vector<int> v4(v3);
    REQUIRE_EQ(v4.size(), 0u);
}

TEST(vector, can_be_copied_by_assignment) {
    vector<int> v1{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> v2;
    v2 = v1;
    REQUIRE_EQ(v1.size(), 10u);
    REQUIRE_EQ(v2.size(), 10u);
    for (auto it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2) {
        REQUIRE_EQ(*it1, *it2);
    }
    vector<int> v3;
    v2 = v3;
    REQUIRE_EQ(v2.size(), 0u);
}

TEST(vector, can_be_moved_by_assignment) {
    vector<int> v1{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> v2;
    v2 = move(v1);
    REQUIRE_EQ(v1.size(), 0u);
    REQUIRE_EQ(v2.size(), 10u);
    REQUIRE_EQ(v2[0], 9);
    REQUIRE_EQ(v2[5], 4);
    REQUIRE_EQ(v2[9], 0);
    vector<int> v3;
    v2 = move(v3);
    REQUIRE_EQ(v2.size(), 0u);
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

TEST(vector, can_pop_back) {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    v.pop_back();
    REQUIRE_EQ(v.size(), 6u);
    REQUIRE_EQ(v.front(), 1);
    REQUIRE_EQ(v.back(), 6);
    v.pop_back();
    REQUIRE_EQ(v.size(), 5u);
    REQUIRE_EQ(v.front(), 1);
    REQUIRE_EQ(v.back(), 5);
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

namespace {

template <typename Type>
void check_const_vector(const vector<Type> &v, unsigned expected_size) {
    auto size = 0u;
    for (const auto &e : v) {
        (void)e;
        size++;
    }
    REQUIRE_EQ(size, expected_size);
}

} // namespace

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

namespace {

template <typename Type>
void test_with_type() {
    vector<Type> v;
    v.push_back(Type());
    REQUIRE(v.front() == Type());
    REQUIRE(v.back() == Type());
    v.push_back(Type() + 2);
    REQUIRE(v.front() == Type());
    REQUIRE(v.back() == Type() + 2);
    v.push_back(Type() + 12);
    REQUIRE(v.front() == Type());
    REQUIRE(v.back() == Type() + 12);
    REQUIRE_EQ(v.size(), 3u);
    v.clear();
    REQUIRE_EQ(v.size(), 0u);
    for (int i = 0; i < 1024; ++i) {
        v.push_back(Type());
    }
    REQUIRE_EQ(v.size(), 1024u);
    for (int i = 0; i < 1024; ++i) {
        v.pop_back();
    }
    REQUIRE_EQ(v.size(), 0u);
}

} // namespace

TEST(vector, works_with_simple_types) {
    test_with_type<char>();
    test_with_type<signed char>();
    test_with_type<unsigned char>();
    test_with_type<short>();
    test_with_type<unsigned short>();
    test_with_type<int>();
    test_with_type<unsigned int>();
    test_with_type<long>();
    test_with_type<long long>();
}

