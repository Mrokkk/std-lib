#include <vector.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(vector, can_be_created) {
    vector<int> v;
    REQUIRE(v.empty());
    REQUIRE_EQ(v.size(), 0u);
    REQUIRE(v.begin() == nullptr);
    REQUIRE(v.end() == nullptr);
}


