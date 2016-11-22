#include <optional.h>
#include <gtest/gtest.h>

TEST(optional, canHaveOptionalValue) {
    optional<int> opt1;
    auto result = opt1.has_value();
    EXPECT_FALSE(result);
    optional<int> opt2(2);
    result = opt2.has_value();
    EXPECT_TRUE(result);
}



