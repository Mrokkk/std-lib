#include <optional.h>
#include "yatf/include/yatf.h"

namespace {

template <typename T>
void test_no_value() {
    optional<T> opt;
    REQUIRE_FALSE(opt);
    REQUIRE_FALSE(opt.has_value());
    REQUIRE_FALSE(opt == T{});
    REQUIRE(opt != T{});
    REQUIRE(opt == optional<T>());
    REQUIRE(optional<T>() == opt);
    REQUIRE_FALSE(opt != optional<T>());
    REQUIRE_FALSE(optional<T>() != opt);
    REQUIRE_FALSE(opt == optional<T>(T{}));
    REQUIRE_FALSE(optional<T>(T{}) == opt);
}

} // namespace anon

TEST(optional, can_have_no_value) {
    test_no_value<int>();
    test_no_value<char>();
    test_no_value<float>();
    test_no_value<double>();
    optional<int> opt;
    for (signed char i = -127; i < 127; i++) {
        REQUIRE_FALSE(opt == (signed char)3);
        REQUIRE(opt != (signed char)3);
        REQUIRE_FALSE(opt > i);
        REQUIRE_FALSE(opt >= i);
        REQUIRE_FALSE(opt < i);
        REQUIRE_FALSE(opt <= i);
    }
}

TEST(optional, can_set_value) {
    optional<int> opt;
    opt = 4;
    REQUIRE(opt);
    REQUIRE(opt.has_value());
    REQUIRE(opt.value() == 4);
    REQUIRE(opt == 4);
    REQUIRE_FALSE(opt == 5);
    REQUIRE(opt != -4);
    REQUIRE_FALSE(opt != 4);
    REQUIRE(opt < 5);
    REQUIRE_FALSE(opt < 2);
    REQUIRE(opt <= 4);
    REQUIRE_FALSE(opt <= 2);
    REQUIRE(opt > 2);
    REQUIRE_FALSE(opt > 5);
    REQUIRE(opt >= 4);
    REQUIRE_FALSE(opt >= 9);
    REQUIRE(opt == optional<int>(4));
    REQUIRE(optional<int>(4) == opt);
    REQUIRE(opt != optional<int>(10));
    REQUIRE(optional<int>(10) != opt);
    REQUIRE_FALSE(opt == optional<int>());
    REQUIRE_FALSE(optional<int>() == opt);
    REQUIRE(opt != optional<int>());
    REQUIRE(optional<int>() != opt);
}

