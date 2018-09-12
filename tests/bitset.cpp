#include <bitset.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(bitset, can_be_created)
{
    bitset<32> bs;
    REQUIRE_EQ(bs.size(), 32u);
    for (auto i = 0u; i < 32u; ++i)
    {
        REQUIRE_FALSE(bs[i]);
    }
}

TEST(bitset, can_assign_value_to_bit)
{
    bitset<32> bs;
    bs[12] = true;
    REQUIRE(bs[12]);
    REQUIRE_FALSE(bs[11]);
    REQUIRE_FALSE(bs[13]);
    bs[12] = false;
    REQUIRE_FALSE(bs[12]);
    REQUIRE_FALSE(bs[11]);
    REQUIRE_FALSE(bs[13]);
    REQUIRE(bs[12] == false);
}

TEST(bitset, can_set_reset_and_flip_bits)
{
    bitset<128> bs;
    bs.set(124);
    REQUIRE(bs[124]);
    bs.reset(124);
    REQUIRE_FALSE(bs[124]);
    bs.flip(124);
    REQUIRE(bs[124]);
    bs.flip(124);
    REQUIRE_FALSE(bs[124]);
}

