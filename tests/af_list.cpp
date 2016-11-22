#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {

struct helper {
    int a;
    af_list<helper> list;
    helper(int x) : a(x), list(&helper::list) {}
};

void testAdding(af_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.add(&e.list);
    head.for_each_entry(&helper::list, [&] (helper *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, s);
    EXPECT_EQ(head.empty(), false);
}

void testAddingFront(af_list<helper> &head, helper &e, std::vector<int> &comp, int s) {
    auto size = 0;
    head.add_front(&e.list);
    head.for_each_entry(&helper::list, [&] (helper *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, s);
    EXPECT_EQ(head.empty(), false);
}

void testDeleting(af_list<helper> &head, helper &e, std::vector<int> &comp) {
    e.list.del();
    size_t size = 0;
    head.for_each_entry(&helper::list, [&] (helper *h) {
        EXPECT_EQ(comp[size], h->a);
        size++;
    });
    EXPECT_EQ(size, comp.size());
    EXPECT_EQ(head.empty(), false);
}

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    af_list<helper> list;
    EXPECT_EQ(list.empty(), true);
}

TEST(AFListTests, canAccesElement) {
    for (auto i = 0; i < 1024; i++) {
        helper e(i);
        auto result = e.list.entry();
        EXPECT_EQ(result->a, i);
    }
}

TEST(AFListTests, canAddElements) {
    af_list<helper> list;
    helper e1(2), e2(44), e3(26), e4(94), e5(24);
    std::vector<int> v{2, 44, 26, 94};
    testAdding(list, e1, v, 1);
    testAdding(list, e2, v, 2);
    testAdding(list, e3, v, 3);
    testAdding(list, e4, v, 4);
    std::vector<int> v2{24, 2, 44, 26, 94};
    testAddingFront(list, e5, v2, 5);
}

TEST(AFListTests, canDeleteElements) {
    af_list<helper> list(&helper::list);
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    testAdding(list, e1, v, 1);
    testAdding(list, e2, v, 2);
    testAdding(list, e3, v, 3);
    testAdding(list, e4, v, 4);
    std::vector<int> v2{2, 44, 94};
    testDeleting(list, e3, v2);
    std::vector<int> v3{44, 94};
    testDeleting(list, e1, v3);
}

