#include <inherited_list.h>
#include <gtest/gtest.h>
#include <iostream>

struct helper : inherited_list<helper> {
    int a = 0;
    helper(int x) : a(x) {}
};

TEST(inherited_list, can_create_empty) {
    helper h(2);
    ASSERT_EQ(&h, h.prev);
    ASSERT_EQ(&h, h.next);
    ASSERT_EQ(h.a, 2);
}

TEST(inherited_list, can_add_elements) {
    inherited_list<helper> head;
    helper h1(2), h2(34), h3(29);
    head.add(&h1);
    ASSERT_EQ(head.next->a, 2);
    ASSERT_EQ(head.next, &h1);
    ASSERT_EQ(head.prev, &h1);
    ASSERT_EQ(head.next->next, &head);
    head.add(&h2);
    ASSERT_EQ(head.next->a, 2);
    ASSERT_EQ(head.next->next->a, 34);
    ASSERT_EQ(head.next, &h1);
    ASSERT_EQ(head.next->next, &h2);
    ASSERT_EQ(head.prev, &h2);
}

