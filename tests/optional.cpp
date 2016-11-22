#include <optional.h>
#include <gtest/gtest.h>

TEST(optional, canHaveOptionalValue) {
    optional<int> opt1;
    auto result = opt1.has_value();
    EXPECT_FALSE(result);
    EXPECT_FALSE(opt1);
    optional<int> opt2(2);
    result = opt2.has_value();
    EXPECT_TRUE(result);
    EXPECT_TRUE(opt2);
    EXPECT_EQ(opt2.value(), 2);
    EXPECT_EQ(opt2.value_or(3), 2);
    int temp = 4;
    EXPECT_EQ(opt2.value_or(temp), 2);
    EXPECT_TRUE(opt2.value() == 2);
}



