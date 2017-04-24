#include <inherited_list.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "yatf/include/yatf.h"

using namespace yacppl;

namespace {

struct helper : inherited_list<helper>::node {
    int a = 0;
    helper(int x) : a(x) {}
};

void init_vectors(std::vector<int> &int_vec, std::vector<helper> &helper_vec, int size) {
    std::srand(std::time(0));
    for (auto i = 0; i < size; i++) {
        int_vec.push_back(std::rand());
    }
    for (auto e : int_vec) {
        helper_vec.push_back(helper{e});
    }
}

void test_adding(inherited_list<helper> &head, int s) {
    std::vector<int> v;
    std::vector<helper> helper_vec;
    init_vectors(v, helper_vec, s);
    REQUIRE(head.empty());
    auto expected_size = 1;
    for (auto &h : helper_vec) {
        auto size = 0;
        head.push_back(&h);
        for (const auto &h : head) {
            REQUIRE_EQ(v[size], h.a);
            size++;
        };
        REQUIRE_FALSE(head.empty());
        REQUIRE_EQ(size, expected_size);
        expected_size++;
    }
}

void test_adding_front(inherited_list<helper> &head, int s) {
    std::vector<int> v;
    std::vector<helper> helper_vec;
    init_vectors(v, helper_vec, s);
    REQUIRE(head.empty());
    auto expected_size = 1;
    for (auto &h : helper_vec) {
        auto size = 0;
        head.push_front(&h);
        for (const auto &h : head) {
            REQUIRE_EQ(v[expected_size - 1 - size], h.a);
            size++;
        };
        REQUIRE_FALSE(head.empty());
        REQUIRE_EQ(size, expected_size);
        expected_size++;
    }
}

} // namespace anon

TEST(inherited_list, can_create_empty) {
    inherited_list<helper> h;
    REQUIRE(h.empty());
}

TEST(inherited_list, can_add_elements) {
    inherited_list<helper> head;
    test_adding(head, 1024);
}

TEST(inherited_list, can_add_elements_front) {
    inherited_list<helper> head;
    test_adding_front(head, 1024);
}

TEST(inherited_list, can_remove) {
    inherited_list<helper> head;
    std::vector<helper> helper_vec{0, 2, 4};
    for (auto &v : helper_vec) {
        head.push_back(&v);
    }
    head.erase(helper_vec[0]);
    std::vector<int> test_vector;
    int size = 0;;
    for (auto &e : head) {
        test_vector.push_back(e.a);
        size++;
    }
    REQUIRE_EQ(test_vector[0], 2);
    REQUIRE_EQ(test_vector[1], 4);
    REQUIRE_EQ(size, 2);
}

TEST(inherited_list, can_use_iterator) {
    inherited_list<helper> head;
    std::vector<helper> helper_vec{0, 2, 4, 9, 30, 109, 938, -231, 3, -29};
    for (auto &v : helper_vec) {
        head.push_back(&v);
    }
    auto it = head.begin();
    REQUIRE_EQ(it->a, 0);
    ++it;
    REQUIRE_EQ(it->a, 2);
    ++it;
    REQUIRE_EQ(it->a, 4);
    --it;
    REQUIRE_EQ(it->a, 2);
    it++;
    REQUIRE_EQ(it->a, 4);
    it++;
    REQUIRE_EQ(it->a, 9);
    ++it;
    REQUIRE_EQ(it->a, 30);
    it++;
    auto h = *it;
    REQUIRE_EQ(h.a, 109);
    auto const_it = head.cbegin();
    REQUIRE_EQ(const_it->a, 0);
    const_it++;
    REQUIRE_EQ(const_it->a, 2);
    ++const_it;
    REQUIRE_EQ(const_it->a, 4);
    const_it = head.cend();
    const_it--;
    REQUIRE_EQ(const_it->a, -29);
    --const_it;
    REQUIRE_EQ(const_it->a, 3);
}

void check_const_inherited_list(const inherited_list<helper> &list) {
    for (const auto &i : list) {
        REQUIRE_EQ(i.a, 4);
    }
}

TEST(inherited_list, works_with_range_based_for) {
    inherited_list<helper> list1;
    std::vector<helper> helper_vec{1, 2, 4, 9, 30, 109, 938, -231, 3, -29};
    for (auto &v : helper_vec) {
        list1.push_back(&v);
    }
    auto size = 0u;
    for (auto &i : list1) {
        REQUIRE(i.a != 0);
        i.a = 4;
        size++;
    }
    REQUIRE_EQ(size, 10u);
    size = 0u;
    for (const auto &i : list1) {
        REQUIRE_EQ(i.a, 4);
        size++;
    }
    REQUIRE_EQ(size, 10u);
    check_const_inherited_list(list1);
}

