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

TEST(vector, can_be_created_from_initializer_list) {
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    // REQUIRE_EQ(v.size(), 7u);
}

