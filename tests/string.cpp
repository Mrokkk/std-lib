#include <string.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(string, can_be_created) {
    string str;
    REQUIRE(str == "");
    REQUIRE_FALSE(str == "abc");
}

TEST(string, can_be_constructed_from_cstring) {
    string str("test_string");
    REQUIRE(str == "test_string");
    REQUIRE_EQ(*(str.cend() - 1), 'g');
    REQUIRE_EQ(*(str.end() - 1), 'g');
    REQUIRE_EQ(*(str.cbegin()), 't');
    REQUIRE_EQ(*(str.begin()), 't');
}

TEST(string, can_be_appended) {
    {
        string str("hello ");
        str.append("world");
        REQUIRE_EQ((const char *)str, "hello world");
    }
    {
        string str;
        str.append("world");
        REQUIRE_EQ((const char *)str, "world");
        str.append("hello hello hello");
        REQUIRE_EQ((const char *)str, "worldhello hello hello");
    }
}

