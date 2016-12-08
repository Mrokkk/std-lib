#include <range.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(range, can_create_string_range) {
    auto str = "test";
    auto a = make_range(str);
    auto i = 0u;
    for (auto it : a) {
        REQUIRE_EQ(it, "test"[i]);
        ++i;
    }
    REQUIRE_EQ(a.size(), 4u);
    REQUIRE_EQ(i, 4u);
}

TEST(range, can_create_int_array_range) {
    int t[] = {1, 2, 4, 5};
    auto b = make_range(t);
    auto i = 0u;
    for (auto it : b) {
        REQUIRE_EQ(it, t[i]);
        ++i;
    }
    REQUIRE_EQ(b.size(), 4u);
    REQUIRE_EQ(i, 4u);
}

