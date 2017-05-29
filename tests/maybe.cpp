#include <maybe.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(maybe, can_be_initialized_by_value) {
    maybe<char> may(32);
    REQUIRE(may);
    REQUIRE_EQ(*may, 32);
}

TEST(maybe, can_be_initialized_by_error) {
    maybe<char> may(error(12));
    REQUIRE_FALSE(may);
    REQUIRE_EQ(may.get_error(), 12u);
}

