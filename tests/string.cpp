#include <string.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(string, can_be_created) {
    string str;
    REQUIRE(str == "");
    REQUIRE(str.empty());
    REQUIRE_EQ(str.length(), 0u);
    REQUIRE_EQ(str.size(), 0u);
    REQUIRE_FALSE(str == "abc");
}

TEST(string, can_be_constructed_from_cstring) {
    {
        string str("test_string");
        REQUIRE(str == "test_string");
        REQUIRE_EQ(str.length(), 11u);
        REQUIRE_EQ(str.size(), 11u);
        REQUIRE_EQ(*(str.cend() - 1), 'g');
        REQUIRE_EQ(*(str.end() - 1), 'g');
        REQUIRE_EQ(*(str.cbegin()), 't');
        REQUIRE_EQ(*(str.begin()), 't');
    }
    {
        string str("test_string", 4);
        REQUIRE(str == "test");
        REQUIRE_EQ(str.length(), 4u);
        REQUIRE_EQ(str.size(), 4u);
        REQUIRE_EQ(*(str.cend() - 1), 't');
        REQUIRE_EQ(*(str.end() - 1), 't');
        REQUIRE_EQ(*(str.cbegin()), 't');
        REQUIRE_EQ(*(str.begin()), 't');
    }
}

TEST(string, can_be_iterated) {
    string str("test_string");
    size_t i = 0;
    for (auto c : str) {
        REQUIRE_EQ(c, "test_string"[i++]);
    }
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
        REQUIRE_EQ(str.length(), 22u);
        str.append(" test test");
        REQUIRE_EQ((const char *)str, "worldhello hello hello test test");
        REQUIRE_EQ(str.length(), 32u);
    }
}

TEST(string, can_get_substring) {
    string str("hello world");
    auto str2 = str.substring(6, 5);
    REQUIRE_EQ((const char *)str2, "world");
    auto str3 = str.substring(6, 1024);
    REQUIRE_EQ((const char *)str3, "world");
    auto str4 = str.substring(11, 1024);
    REQUIRE_EQ((const char *)str4, "");
}

TEST(string, can_be_erased) {
    string str("hello world");
    str.erase(str.begin() + 5, str.end());
    REQUIRE_EQ((const char *)str, "hello");
    REQUIRE_EQ(str.length(), 5u);
    REQUIRE_EQ(str.size(), 11u);
    REQUIRE(not str.empty());
    str.erase(str.end() - 1, str.end());
    REQUIRE_EQ((const char *)str, "hell");
    REQUIRE_EQ(str.length(), 4u);
    REQUIRE_EQ(str.size(), 11u);
    REQUIRE(not str.empty());
}

TEST(string, cannot_be_erased_if_begin_after_end) {
    string str("hello world");
    str.erase(str.end(), str.begin());
    REQUIRE_EQ((const char *)str, "hello world");
}

