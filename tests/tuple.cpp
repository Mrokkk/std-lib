#include <tuple.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(tuple, can_be_created)
{
    {
        tuple<int> t(-923);
        REQUIRE_EQ(t.get<0>(), -923);
        REQUIRE_EQ(t.size(), 1u);
    }

    {
        tuple<int, char> t(2, 'c');
        REQUIRE_EQ(t.get<0>(), 2);
        REQUIRE_EQ(t.get<1>(), 'c');
        REQUIRE_EQ(t.size(), 2u);
    }

    {
        tuple<int, char, unsigned int> t(9835, 'c', 123);
        REQUIRE_EQ(t.get<0>(), 9835);
        REQUIRE_EQ(t.get<1>(), 'c');
        REQUIRE_EQ(t.get<2>(), 123u);
        REQUIRE_EQ(t.size(), 3u);
    }
}

