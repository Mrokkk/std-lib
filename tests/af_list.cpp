#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {
struct helper {
    int a;
    af_list::list_head list;
    helper(int x) : a(x) {}
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

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    af_list::list_head list;
    EXPECT_EQ(list.empty(), true);
}

TEST(AFListTests, canAddElements) {
    af_list::list_head testList;
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    addTest(testList, e1, v, 1);
    addTest(testList, e2, v, 2);
    addTest(testList, e3, v, 3);
    addTest(testList, e4, v, 4);
}

TEST(AFListTests, canDeleteElements) {
}

