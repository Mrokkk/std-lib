#include <inherited_list.h>
#include <gtest/gtest.h>
#include <vector>

namespace {

struct helper : inherited_list<helper> {
    int a = 0;
    helper(int x) : a(x) {}
};

void testAdding(inherited_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.add(&e);
    for (const auto &h : head) {
        EXPECT_EQ(comp[size], h.a);
        size++;
    };
    EXPECT_EQ(size, s);
    EXPECT_EQ(head.empty(), false);
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
    helper h1(2), h2(34), h3(29);
    std::vector<helper> c{helper{2}, helper{3}};
    std::vector<int> comp{2, 34, 29};
    testAdding(head, h1, comp, 1);
    testAdding(head, h2, comp, 2);
    testAdding(head, h3, comp, 3);
}

