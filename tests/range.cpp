#include <range.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(range, can_create) {
    auto str = "test";
    auto a = make_range(str);
    auto i = 0u;
    for (auto it : a) {
        REQUIRE_EQ(it, str[i]);
        ++i;
    }
    REQUIRE_EQ(a.size(), 4u);
    REQUIRE_EQ(i, 4u);
    int t[] = {1, 2, 4, 5};
    auto b = make_range(t);
    REQUIRE_EQ(b.size(), 4u);
}

