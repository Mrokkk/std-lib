#include <static_string.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(static_string, can_create_empty) {
    static_string<16> string;
    REQUIRE_EQ(string.length(), 0u);
    REQUIRE_EQ(string.size(), 16u);
    for (int i = 0; i < 16; i++)
        REQUIRE_EQ(string[i], 0);
}

TEST(static_string, can_write_to) {
    static_string<32> string;
    string = "test";
    REQUIRE_EQ(string.length(), 4u);
    REQUIRE(string == "test");
    REQUIRE_FALSE(string == "random");
}

