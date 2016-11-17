#include <af_list.h>
#include <gtest/gtest.h>

using namespace yacppl;

namespace {

struct helper {
    int a, b, c;
    char d, e, f;
    list_head list;
};

} // namespace anon

TEST(AFListTests, canCreateEmpty) {
    list_head list;
    EXPECT_EQ(af_list::list_empty(&list), true);
}

