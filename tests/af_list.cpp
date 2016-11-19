#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {
struct helper {
    int a;
    af_list::list_head list;
    helper(int x) : a(x) {}
};

struct helper2 {
    int a;
    af_list::af_list<helper2> list;
    helper2(int x) : a(x) {}
};

void addTest(af_list::list_head &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    list_add_tail(&e.list, &head);
    af_list::list_for_each_entry(&head, &helper::list, [&] (helper *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, s);
    EXPECT_EQ(head.empty(), false);
}

void addTest2(af_list::af_list<helper2> &head, helper2 &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.add(&e.list);
    head.for_each_entry(&helper2::list, [&] (helper2 *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, s);
    EXPECT_EQ(head.empty(), false);
}

void delTest(af_list::list_head &head, helper &e, std::vector<int> &comp) {
    af_list::list_del(&e.list);
    size_t size = 0;
    af_list::list_for_each_entry(&head, &helper::list, [&] (helper *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, comp.size());
    EXPECT_EQ(head.empty(), false);
}

void delTest2(af_list::af_list<helper2> &head, helper2 &e, std::vector<int> &comp) {
    e.list.del();
    size_t size = 0;
    head.for_each_entry(&helper2::list, [&] (helper2 *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, comp.size());
    EXPECT_EQ(head.empty(), false);
}

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    af_list::list_head list;
    EXPECT_EQ(list.empty(), true);
}

TEST(AFListTests, canAccesElement) {
    for (auto i = 0; i < 1024; i++) {
        helper e(i);
        auto result = af_list::list_entry<helper>(&e.list, offsetof(helper, list));
        EXPECT_EQ(result->a, i);
    }
}

TEST(AFListTests2, canAccesElement) {
    for (auto i = 0; i < 1024; i++) {
        helper2 e(i);
        auto result = e.list.entry(&e.list, offsetof(helper, list));
        EXPECT_EQ(result->a, i);
    }
}

TEST(AFListTests, canAddElements) {
    af_list::list_head list;
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    addTest(list, e1, v, 1);
    addTest(list, e2, v, 2);
    addTest(list, e3, v, 3);
    addTest(list, e4, v, 4);
}

TEST(AFListTests2, canAddElements) {
    af_list::af_list<helper2> list;
    helper2 e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    addTest2(list, e1, v, 1);
    addTest2(list, e2, v, 2);
    addTest2(list, e3, v, 3);
    addTest2(list, e4, v, 4);
}

TEST(AFListTests, canDeleteElements) {
    af_list::list_head list;
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    addTest(list, e1, v, 1);
    addTest(list, e2, v, 2);
    addTest(list, e3, v, 3);
    addTest(list, e4, v, 4);
    std::vector<int> v2{2, 44, 94};
    delTest(list, e3, v2);
    std::vector<int> v3{44, 94};
    delTest(list, e1, v3);
}

TEST(AFListTests2, canDeleteElements) {
    af_list::af_list<helper2> list;
    helper2 e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    addTest2(list, e1, v, 1);
    addTest2(list, e2, v, 2);
    addTest2(list, e3, v, 3);
    addTest2(list, e4, v, 4);
    std::vector<int> v2{2, 44, 94};
    delTest2(list, e3, v2);
    std::vector<int> v3{44, 94};
    delTest2(list, e1, v3);
}

