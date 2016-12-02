#include <inherited_list.h>
#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace yacppl;

namespace {

struct helper : inherited_list<helper> {
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
    ASSERT_TRUE(head.empty());
    auto expected_size = 1;
    for (auto &h : helper_vec) {
        auto size = 0;
        head.add(&h);
        for (const auto &h : head) {
            EXPECT_EQ(v[size], h.a);
            size++;
        };
        EXPECT_EQ(head.empty(), false);
        EXPECT_EQ(size, expected_size);
        expected_size++;
    }
}

void test_adding_front(inherited_list<helper> &head, int s) {
    std::vector<int> v;
    std::vector<helper> helper_vec;
    init_vectors(v, helper_vec, s);
    ASSERT_TRUE(head.empty());
    auto expected_size = 1;
    for (auto &h : helper_vec) {
        auto size = 0;
        head.add_front(&h);
        for (const auto &h : head) {
            EXPECT_EQ(v[expected_size - 1 - size], h.a);
            size++;
        };
        EXPECT_EQ(head.empty(), false);
        EXPECT_EQ(size, expected_size);
        expected_size++;
    }
}

} // namespace anon

TEST(inherited_list, can_create_empty) {
    helper h(2);
    ASSERT_EQ(h.prev(), nullptr);
    ASSERT_EQ(h.next(), nullptr);
    ASSERT_EQ(h.a, 2);
    ASSERT_TRUE(h.empty());
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
        head.add(&v);
    }
    helper_vec[0].remove();
    std::vector<int> test_vector;
    int size = 0;;
    for (auto &e : head) {
        test_vector.push_back(e.a);
        size++;
    }
    ASSERT_EQ(test_vector[0], 2);
    ASSERT_EQ(test_vector[1], 4);
    ASSERT_EQ(size, 2);
}

