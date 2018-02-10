#include <string.hpp>
#include "yatf/include/yatf.hpp"

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

string get_string() {
    return "some_string";
}

TEST(string, can_be_created_from_other_string) {
    string str("test_string");
    {
        auto str2 = str;
        REQUIRE(not str.empty());
        REQUIRE(not str2.empty());
        REQUIRE(str == "test_string");
        REQUIRE(str2 == "test_string");
    }
    {
        string str2(str);
        REQUIRE(not str.empty());
        REQUIRE(not str2.empty());
        REQUIRE(str == "test_string");
        REQUIRE(str2 == "test_string");
    }
    {
        string str2;
        string str3(str2);
        REQUIRE_EQ(str3.operator const char *(), nullptr);
    }
    {
        string str2("some_string");
        string str3(move(str2));
        REQUIRE_EQ(str2.operator const char *(), nullptr);
        REQUIRE(str3 == "some_string");
    }
    str = string("some");
    REQUIRE(str == "some");
    str = string("some very, very, very long string");
    REQUIRE(str == "some very, very, very long string");
    str = nullptr;
    REQUIRE(!str);
    str = "something";
    REQUIRE(str == "something");
    auto str2 = get_string();
    REQUIRE(str2 == "some_string");
    str = str2;
    REQUIRE(str == "some_string");
    // FIXME
    str = string();
    str = string(str2);
    str = string();
    str = string(string("some other"));
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

TEST(string, can_append_chars) {
    string str;
    for (auto i = 0u; i < 1024u; ++i) {
        str.append('a');
        REQUIRE_EQ(str.length(), i + 1);
    }
}

TEST(string, can_reserve_size) {
    string str;
    str.reserve(1024);
    REQUIRE_EQ(str.size(), 1024u);
    for (auto i = 0u; i < 1023u; ++i) {
        str.append('a');
        REQUIRE_EQ(str.length(), i + 1);
        REQUIRE_EQ(str.size(), 1024u);
    }
    str.append('c');
    REQUIRE(str.size() != 1024u);
    str.reserve(4096);
    REQUIRE_EQ(str.size(), 4096u);
}

TEST(string, split_on_empty_string_should_return_empty_vec) {
    string str;
    const auto splitted = str.split();
    REQUIRE_EQ(splitted.size(), 0u);
}

TEST(string, can_split) {
    {
        string str("some");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 1u);
        REQUIRE_EQ((const char *)splitted[0], "some");
    }
    {
        string str("some string");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str("some string ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str("some string  ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str("  some string  ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str(" some string  ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str(" some   string  ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 2u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "string");
    }
    {
        string str(" some   other string  ");
        const auto splitted = str.split();
        REQUIRE_EQ(splitted.size(), 3u);
        REQUIRE_EQ((const char *)splitted[0], "some");
        REQUIRE_EQ((const char *)splitted[1], "other");
        REQUIRE_EQ((const char *)splitted[2], "string");
    }
}

