#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {

struct helper {
    int a;
    af_list::list_head list;
    helper(int x) : a(x) {}
};

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    af_list::list_head list;
    EXPECT_EQ(list.empty(), true);
}

TEST(AFListTests, canAddElements) {
    af_list::list_head testList;
    helper e1(2), e2(44), e3(26), e4(94);
    std::vector<int> v{2, 44, 26, 94};
    list_add_tail(&e1.list, &testList);
    helper *temp;
    auto size = 0;
    list_for_each_entry(temp, &testList, list) {
        EXPECT_EQ(v[size], temp->a);
        size++;
    }
    EXPECT_EQ(size, 1);
    EXPECT_EQ(testList.empty(), false);

    size = 0;
    list_add_tail(&e2.list, &testList);
    list_for_each_entry(temp, &testList, list) {
        EXPECT_EQ(v[size], temp->a);
        size++;
    }
    EXPECT_EQ(size, 2);
    EXPECT_EQ(testList.empty(), false);

    size = 0;
    list_add_tail(&e3.list, &testList);
    list_for_each_entry(temp, &testList, list) {
        EXPECT_EQ(v[size], temp->a);
        size++;
    }
    EXPECT_EQ(size, 3);
    EXPECT_EQ(testList.empty(), false);
}

