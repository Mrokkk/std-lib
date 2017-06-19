#include <pair.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(pair, can_be_created_empty) {
    pair<int, int> p;
    REQUIRE_EQ(p.first, int());
    REQUIRE_EQ(p.second, int());
}

TEST(pair, can_be_initialized) {
    pair<int, int> p(3, -254);
    REQUIRE_EQ(p.first, 3);
    REQUIRE_EQ(p.second, -254);
}

TEST(pair, can_be_created_by_make_pair) {
    auto p = make_pair(45, -835);
    REQUIRE_EQ(p.first, 45);
    REQUIRE_EQ(p.second, -835);
}

TEST(pair, can_be_compared) {
    auto p1 = make_pair(45, 33);
    auto p2 = make_pair(45, -835);
    REQUIRE(p1 != p2);
    auto p3 = make_pair(2, 8532);
    auto p4 = make_pair(45, 8532);
    REQUIRE(p3 != p4);
    REQUIRE(p3 != p1);
    auto p5 = make_pair(2, 8532);
    REQUIRE(p5 == p3);
}

