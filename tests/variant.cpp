#include <new>
#include <variant.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

struct helper {
    int a, b, c;
};

TEST(variant, can_be_created_empty) {
    variant<int> v1;
    REQUIRE_EQ(v1.get<int>(), 0);
    variant<int, char> v2;
    REQUIRE_EQ(v2.get<int>(), 0);
    REQUIRE_EQ(v2.get<char>(), 0);
    variant<int, char, helper> v3;
    REQUIRE_EQ(v3.get<int>(), 0);
    REQUIRE_EQ(v3.get<char>(), 0);
}

TEST(variant, can_be_created_from_value) {
    variant<int, char, helper> v1(32);
    REQUIRE_EQ(v1.get<int>(), 32);
    variant<int, char, helper> v2('c');
    REQUIRE_EQ(v2.get<char>(), 'c');
    variant<int, char, helper> v3(helper{1, 2, 3});
    REQUIRE_EQ(v3.get<helper>().a, 1);
    REQUIRE_EQ(v3.get<helper>().b, 2);
    REQUIRE_EQ(v3.get<helper>().c, 3);
}

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

TEST(variant, can_be_assigned) {
    variant<int, char, helper> v;
    v = -921;
    REQUIRE_EQ(v.get<int>(), -921);
    v = 'f';
    REQUIRE_EQ(v.get<char>(), 'f');
    v = helper{1, 2, 4};
    REQUIRE_EQ(v.get<helper>().a, 1);
    REQUIRE_EQ(v.get<helper>().b, 2);
    REQUIRE_EQ(v.get<helper>().c, 4);
}

