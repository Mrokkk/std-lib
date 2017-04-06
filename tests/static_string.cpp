#include <static_string.h>
#include <string.h>
#include <algorithm.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(static_string, can_create_empty) {
    static_string<16> string;
    REQUIRE_EQ(string.length(), 0u);
    REQUIRE_EQ(string.size(), 16u);
    for (int i = 0; i < 16; i++)
        REQUIRE_EQ(string[i], 0);
}

TEST(static_string, can_create_from_cstring) {
    const char *str = "hello world";
    static_string<16> string(str);
    REQUIRE_EQ(string.length(), 11u);
    REQUIRE_EQ(string.size(), 16u);
    for (int i = 0; i < 11; i++)
        REQUIRE_EQ(string[i], str[i]);
    REQUIRE(string == str);
}

TEST(static_string, can_write_to) {
    static_string<32> string;
    string = "test";
    REQUIRE_EQ(string.length(), 4u);
    REQUIRE(string == "test");
    REQUIRE_FALSE(string == "random");
    REQUIRE_FALSE(string == "rand");
    REQUIRE(string != "random");
    REQUIRE(string != "rand");
}

TEST(static_string, can_iterate) {
    static_string<32> string;
    string = "test";
    const char *s = "test";
    size_t size = 0;
    for (auto c : string) {
        REQUIRE_EQ(c, s[size]);
        size++;
    }
    REQUIRE(*begin(string) == 't');
    auto str = "test";
    REQUIRE(*cbegin(str) == 't');
    REQUIRE(*cbegin("test") == 't');
    REQUIRE(*(cend("testa") - 1) == 'a');
    REQUIRE(last_occurrence(string, 'a') == cend(string));
}

