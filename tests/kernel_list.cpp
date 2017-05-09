#include <kernel_list.hpp>
#include <vector>
#include "yatf/include/yatf.h"

using namespace yacppl;

namespace {

struct helper {
    int a;
    kernel_list<helper>::node list;
    helper(int x) : a(x) {}
};

void test_adding(kernel_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.push_back(e);
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, s);
    REQUIRE_FALSE(head.empty());
}

void test_adding_front(kernel_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.push_front(e);
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, s);
    REQUIRE_FALSE(head.empty());
}

void test_removing(kernel_list<helper> &head, helper &e, std::vector<int> &comp) {
    head.erase(e);
    size_t size = 0;
    for (const auto &h : head) {
        REQUIRE_EQ(comp[size], h.a);
        size++;
    };
    REQUIRE_EQ(size, comp.size());
    REQUIRE_FALSE(head.empty());
}

} // namespace

TEST(kernel_list, can_create_empty) {
    kernel_list<helper> list(&helper::list);
    REQUIRE(list.empty());
}

TEST(kernel_list, can_add_elements) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94), e5(24);
    std::vector<int> v{2, 44, 26, 94};
    test_adding(list, e1, v, 1);
    test_adding(list, e2, v, 2);
    test_adding(list, e3, v, 3);
    test_adding(list, e4, v, 4);
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

TEST(kernel_list, can_iterate) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94);
    list.push_back(e1);
    list.push_back(e2);
    list.push_back(e3);
    list.push_back(e4);
    auto it = list.begin();
    REQUIRE_EQ(it->a, 2);
    ++it;
    REQUIRE_EQ(it->a, 44);
    it++;
    REQUIRE_EQ(it->a, 26);
    it++;
    REQUIRE_EQ(it->a, 94);
    ++it;
    REQUIRE(it == list.end());
    --it;
    REQUIRE_EQ(it->a, 94);
    it--;
    REQUIRE_EQ(it->a, 26);
    auto const_it = list.cbegin();
    REQUIRE_EQ(const_it->a, 2);
    const_it++;
    REQUIRE_EQ(const_it->a, 44);
    ++const_it;
    REQUIRE_EQ(const_it->a, 26);
}

TEST(kernel_list, can_insert) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94);
    list.push_back(e1);
    list.push_back(e2);
    list.push_back(e3);
    auto it = list.begin();
    it++;
    list.insert(it, e4);
    it = list.begin();
    REQUIRE_EQ(it->a, 2);
    it++;
    REQUIRE_EQ(it->a, 94);
    it++;
    REQUIRE_EQ(it->a, 44);
    it++;
    REQUIRE_EQ(it->a, 26);
    it++;
    REQUIRE(it == list.end());
    helper e5(-924);
    list.insert(e1, e5);
    it = list.begin();
    REQUIRE_EQ(it->a, -924);
    it++;
    REQUIRE_EQ(it->a, 2);
    it++;
    REQUIRE_EQ(it->a, 94);
    it++;
    REQUIRE_EQ(it->a, 44);
    ++it;
    REQUIRE_EQ(it->a, 26);
    ++it;
    REQUIRE(it == list.end());
}

TEST(kernel_list, can_erase) {
    kernel_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94);
    list.push_back(e1);
    list.push_back(e2);
    list.push_back(e3);
    list.push_back(e4);
    auto it = list.begin();
    list.erase(it);
    REQUIRE_EQ(list.begin()->a, 44);
    REQUIRE_FALSE(list.empty());
    it = list.begin();
    it++;
    list.erase(it);
    it = list.begin();
    REQUIRE_EQ(it->a, 44);
    it++;
    REQUIRE_EQ(it->a, 94);
    ++it;
    REQUIRE(it == list.end());
    list.erase(e4);
    it = list.begin();
    REQUIRE_EQ(it->a, 44);
    ++it;
    REQUIRE(it == list.end());
}

