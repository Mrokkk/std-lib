#include <inherited_list.h>
#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace {

struct helper : inherited_list<helper> {
    int a = 0;
    helper(int x) : a(x) {}
};

void testAdding(inherited_list<helper> &head, int s) {
    std::srand(std::time(0));
    std::vector<int> v;
    for (auto i = 0; i < s; i++) {
        v.push_back(std::rand());
    }
    std::vector<helper> helper_vec;
    for (auto e : v) {
        helper_vec.push_back(helper{e});
    }
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

} // namespace anon

TEST(inherited_list, can_create_empty) {
    helper h(2);
    ASSERT_EQ(&h, h.prev());
    ASSERT_EQ(&h, h.next());
    ASSERT_EQ(h.a, 2);
    ASSERT_TRUE(h.empty());
}

TEST(inherited_list, can_add_elements) {
    inherited_list<helper> head;
    testAdding(head, 1024);
}

