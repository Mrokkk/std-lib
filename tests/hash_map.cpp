#include <hash_map.h>
#include "yatf/include/yatf.h"

#include <limits>

using namespace yacppl;

TEST(hash_map, can_create_empty) {
    hash_map<int, int> map;
    REQUIRE_EQ(map.size(), 0u);
}

TEST(hash_map, can_add_elements) {
    hash_map<unsigned, int> map;
    map.insert(make_pair(23u, 43));
    REQUIRE_EQ(map.size(), 1u);
    {
        auto pair = map[23u];
        REQUIRE_EQ(pair->first, 23u);
        REQUIRE_EQ(pair->second, 43);
    }
    map.insert(make_pair(2053u, 4167));
    REQUIRE_EQ(map.size(), 2u);
    {
        auto pair = map[2053u];
        REQUIRE_EQ(pair->first, 2053u);
        REQUIRE_EQ(pair->second, 4167);
    }
    {
        auto pair = map[23u];
        REQUIRE_EQ(pair->first, 23u);
        REQUIRE_EQ(pair->second, 43);
    }
}

TEST(hash_map, cannot_get_nonexistent_element) {
    hash_map<unsigned, int> map;
    for (auto i = 0u; i < 1024u; ++i) {
        auto pair = map[i];
        REQUIRE_FALSE(pair);
    }
    map.insert(make_pair(23u, 43));
    for (auto i = 0u; i < 23u; ++i) {
        auto pair = map[i];
        REQUIRE_FALSE(pair);
    }
}

TEST(hash_map, can_erase) {
    hash_map<unsigned, int> map;
    map.insert(make_pair(914324u, 32));
    REQUIRE_EQ(map.size(), 1u);
    map.erase(914324u);
    REQUIRE_EQ(map.size(), 0u);
    auto node = map[914324u];
    REQUIRE_FALSE(node);
    map.insert(make_pair(914324u, 9));
    map.insert(make_pair(0u, 823));
    map.insert(make_pair(324u, -125));
    map.insert(make_pair(13u, 0));
    map.insert(make_pair(923482455u, 1994));
    REQUIRE_EQ(map.size(), 5u);
    map.erase(13u);
    REQUIRE_EQ(map.size(), 4u);
    REQUIRE_FALSE(map[13u]);
    map.erase(0u);
    REQUIRE_EQ(map.size(), 3u);
    REQUIRE_FALSE(map[0u]);
    map.erase(324u);
    REQUIRE_EQ(map.size(), 2u);
    REQUIRE_FALSE(map[324u]);
    map.erase(914324u);
    REQUIRE_EQ(map.size(), 1u);
    REQUIRE_FALSE(map[914324u]);
    map.erase(923482455u);
    REQUIRE_EQ(map.size(), 0u);
    REQUIRE_FALSE(map[923482455u]);
}

TEST(hash_map, cannot_erase_nonexisting_keys) {
    hash_map<unsigned, int> map;
    for (auto i = 0u; i < 1024u; ++i) {
        map.erase(i);
        REQUIRE_EQ(map.size(), 0u);
    }
    map.insert(make_pair(23u, 43));
    for (auto i = 0u; i < 23u; ++i) {
        map.erase(i);
        REQUIRE_EQ(map.size(), 1u);
    }
}

namespace {

template <typename T>
void check_type() {
    hash_map<T, char> map;
    REQUIRE_EQ(map.size(), 0u);
    map.insert(make_pair(T(), 'a'));
    REQUIRE_EQ(map.size(), 1u);
    map.insert(make_pair(std::numeric_limits<T>::max(), 'c'));
    REQUIRE_EQ(map.size(), 2u);
    {
        auto pair = map[T()];
        REQUIRE(pair);
        REQUIRE_EQ(pair->second, 'a');
    }
    {
        auto pair = map[std::numeric_limits<T>::max()];
        REQUIRE(pair);
        REQUIRE_EQ(pair->second, 'c');
    }
    map.erase(T());
    REQUIRE_EQ(map.size(), 1u);
    map.erase(std::numeric_limits<T>::max());
    REQUIRE_EQ(map.size(), 0u);
    for (auto i = 0; i < 255; ++i) {
        REQUIRE_FALSE(map[i]);
    }
    for (auto i = std::numeric_limits<T>::max(); i >= (std::numeric_limits<T>::max() - 254); --i) {
        REQUIRE_FALSE(map[i]);
    }
}

} // namspace

TEST(hash_map, works_with_simple_types_keys) {
    check_type<signed char>();
    check_type<unsigned char>();
    check_type<short>();
    check_type<unsigned short>();
    check_type<int>();
    check_type<unsigned int>();
    check_type<long>();
    check_type<long long>();
}

