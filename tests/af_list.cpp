#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {

struct helper {
    int a, b, c;
    char d, e, f;
    af_list::list_head list;
};

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    af_list::list_head list;
    EXPECT_EQ(af_list::list_empty(&list), true);
}

