#include <gtest/gtest.h>
#include <static_string.h>

using namespace yacppl;

TEST(static_string, can_create_empty) {
    static_string<16> string;
    EXPECT_TRUE(string.length() == 0);
    EXPECT_TRUE(string.size() == 16);
    for (int i = 0; i < 16; i++)
        EXPECT_TRUE(string[i] == 0);
}

