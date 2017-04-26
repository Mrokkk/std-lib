#include <kernel_list.h>
#include <vector>
#include "yatf/include/yatf.h"

using namespace yacppl;

namespace {

struct helper {
    int a;
    kernel_list<helper> list;
    helper(int x) : a(x), list(&helper::list) {}
};

void test_adding(kernel_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.push_back(e.list);
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, s);
    REQUIRE_FALSE(head.empty());
}

void test_adding_front(kernel_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.push_front(e.list);
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, s);
    REQUIRE_FALSE(head.empty());
}

void test_removing(kernel_list<helper> &head, helper &e, std::vector<int> &comp) {
    e.list.remove();
    size_t size = 0;
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, comp.size());
    REQUIRE_FALSE(head.empty());
}

} // namespace anon

TEST(kernel_list, can_create_empty) {
    kernel_list<helper> list(&helper::list);
    REQUIRE(list.empty());
    REQUIRE_EQ(list.next_entry(), nullptr);
    REQUIRE_EQ(list.prev_entry(), nullptr);
}

TEST(kernel_list, can_acces_element) {
    for (auto i = 0; i < 1024; i++) {
        helper e(i);
        auto result = e.list.entry();
        REQUIRE_EQ(result->a, i);
    }
}

TEST(kernel_list, can_add_elements) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94), e5(24);
    std::vector<int> v{2, 44, 26, 94};
    test_adding(list, e1, v, 1);
    test_adding(list, e2, v, 2);
    test_adding(list, e3, v, 3);
    test_adding(list, e4, v, 4);
    REQUIRE_EQ(list.next_entry()->a, v.front());
    REQUIRE_EQ(list.prev_entry()->a, v.back());
    std::vector<int> v2{24, 2, 44, 26, 94};
    test_adding_front(list, e5, v2, 5);
}

TEST(kernel_list, can_delete_elements) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    test_adding(list, e1, v, 1);
    test_adding(list, e2, v, 2);
    test_adding(list, e3, v, 3);
    test_adding(list, e4, v, 4);
    std::vector<int> v2{2, 44, 94};
    test_removing(list, e3, v2);
    std::vector<int> v3{44, 94};
    test_removing(list, e1, v3);
}

