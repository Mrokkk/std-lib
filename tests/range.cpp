#include <range.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(range, can_create_const_string_range) {
    const char *str = "test";
    auto a = make_range(str);
    auto i = 0u;
    for (auto it : a) {
        REQUIRE_EQ(it, "test"[i]);
        ++i;
    }
    REQUIRE_EQ(a.size(), 4u);
    REQUIRE_EQ(i, 4u);
}

TEST(range, can_create_nonconst_string_range) {
    char str[] = "test";
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

struct helper {
    int a;
    helper(int a) : a(a) {}
};

TEST(range, can_create_struct_array_range) {
    helper a[] = {1, 4, 6, 8};
    auto r = make_range(a);
    auto size = 0u;
    for (auto it : r) {
        REQUIRE_EQ(it.a, a[size].a);
        ++size;
    }
    REQUIRE_EQ(r.size(), 4u);
    REQUIRE_EQ(size, 4u);
}

