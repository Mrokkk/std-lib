#include <hash_map.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(hash_map, can_create_empty) {
    hash_map<int, int> map;
    REQUIRE_EQ(map.size(), 0u);
}

TEST(hash_map, can_add_elements) {
    hash_map<unsigned, int> map;
    map.append(make_pair(23u, 43));
    {
        auto pair = map[23u];
        REQUIRE_EQ(pair->first, 23u);
        REQUIRE_EQ(pair->second, 43);
    }
    map.append(make_pair(2053u, 4167));
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
    map.append(make_pair(23u, 43));
    for (auto i = 0u; i < 23u; ++i) {
        auto pair = map[i];
        REQUIRE_FALSE(pair);
    }
}

