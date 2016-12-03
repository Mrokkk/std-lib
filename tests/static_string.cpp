#include <static_string.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(static_string, can_create_empty) {
    static_string<16> string;
    REQUIRE(string.length() == 0);
    REQUIRE(string.size() == 16);
    for (int i = 0; i < 16; i++)
        REQUIRE(string[i] == 0);
}

