#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;


struct helper {
    int a;
    af_list::list_head list;
    helper(int x) : a(x) {}
};


TEST(AFListTests, canCreateEmpty) {
    af_list::list_head list;
    EXPECT_EQ(list.empty(), true);
}

TEST(AFListTests, canAddElements) {
    af_list::list_head testList;
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    list_add_tail(&e1.list, &testList);
    auto size = 0;
    af_list::list_for_each_entry(&testList, &helper::list, [&] (helper *h) {
        EXPECT_EQ(v[size], h->a);
        size++;
    });
    EXPECT_EQ(size, 1);
    EXPECT_EQ(testList.empty(), false);

    size = 0;
    list_add_tail(&e2.list, &testList);
    af_list::list_for_each_entry(&testList, &helper::list, [&] (helper *h) {
        EXPECT_EQ(v[size], h->a);
        size++;
    });
    EXPECT_EQ(size, 2);
    EXPECT_EQ(testList.empty(), false);

    size = 0;
    list_add_tail(&e3.list, &testList);
    af_list::list_for_each_entry(&testList, &helper::list, [&] (helper *h) {
        EXPECT_EQ(v[size], h->a);
        size++;
    });
    EXPECT_EQ(size, 3);
    EXPECT_EQ(testList.empty(), false);
}

