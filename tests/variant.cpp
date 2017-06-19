#include <new>
#include <variant.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(variant, can_be_created) {
    variant<int, char> v;
    REQUIRE_EQ(v.get<int>(), 0);
    REQUIRE_EQ(v.get<char>(), 0);
}

struct helper {
    int a, b, c;
};

TEST(variant, can_be_set) {
    variant<int, char, helper> v;
    v.set<int>(-921);
    REQUIRE_EQ(v.get<int>(), -921);
    v.set<char>('f');
    REQUIRE_EQ(v.get<char>(), 'f');
    v.set<helper>(helper{1, 2, 4});
    REQUIRE_EQ(v.get<helper>().a, 1);
    REQUIRE_EQ(v.get<helper>().b, 2);
    REQUIRE_EQ(v.get<helper>().c, 4);
}

