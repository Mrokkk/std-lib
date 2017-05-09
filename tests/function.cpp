#include <function.hpp>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(function, can_create_empty) {
    function<void()> f;
    REQUIRE_FALSE(f);
}

namespace {

void dummy_function1() {
    REQUIRE(true);
}

void dummy_function2(int a) {
    REQUIRE_EQ(a, 198);
}

int dummy_function3(int a) {
    return a;
}

} // namespace

TEST(function, can_create_from_function_ptr) {
    function<void(void)> f1(&dummy_function1);
    REQUIRE(f1);
    f1();
    function<void(int)> f2(&dummy_function2);
    REQUIRE(f2);
    f2(198);
    function<int(int)> f3(&dummy_function3);
    REQUIRE(f3);
    auto result = f3(126);
    REQUIRE_EQ(result, 126);
}

TEST(function, can_create_from_lambda) {
    function<void(int)> f([](int a){ REQUIRE_EQ(a, 194); });
    REQUIRE(f);
    f(194);
}

TEST(function, can_assign_function_ptr) {
    function<void()> f;
    f = &dummy_function1;
    REQUIRE(f);
    f = nullptr;
    REQUIRE_FALSE(f);
}

TEST(function, can_assign_lambda) {
    function<void(int)> f;
    f = [](int a){ REQUIRE_EQ(a, 194); };
    REQUIRE(f);
    f(194);
}

TEST(function, can_make_function) {
    auto f1 = make_function(&dummy_function1);
    REQUIRE(f1);
    f1();
    auto f2 = make_function(dummy_function2);
    REQUIRE(f2);
    f2(198);
    auto f3 = make_function(dummy_function3);
    REQUIRE(f3);
    auto result = f3(192);
    REQUIRE_EQ(result, 192);
}

