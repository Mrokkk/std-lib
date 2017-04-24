#include <function.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(function, can_create_empty) {
    function<void()> f;
    REQUIRE_FALSE(f);
}

int dummy_function(int a) {
    return a;
}

TEST(function, can_create_from_function_ptr) {
    function<int(int)> f(&dummy_function);
    REQUIRE(f);
    auto result = f(126);
    REQUIRE_EQ(result, 126);
}

