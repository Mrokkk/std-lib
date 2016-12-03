#include <optional.h>
#include "yatf/include/yatf.h"

namespace {

template <typename T>
void test_no_value() {
    optional<T> opt;
    REQUIRE_FALSE(opt);
    REQUIRE_FALSE(opt.has_value());
}

} // namespace anon

TEST(optional, can_have_no_value) {
    test_no_value<int>();
    test_no_value<char>();
    test_no_value<float>();
    test_no_value<double>();
}

