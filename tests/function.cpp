#include <function.hpp>
#include "yatf/include/yatf.hpp"

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
    function<void()> f1(&dummy_function1);
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

TEST(function, can_create_from_capturing_lambda) {
    int a = 129;
    function<void(void)> f([&](){ REQUIRE_EQ(a, 129); });
    REQUIRE(f);
    f();
}

TEST(function, can_assign_function_ptr) {
    function<void()> f;
    f = dummy_function1;
    REQUIRE(f);
    f();
}

TEST(function, can_assign_lambda) {
    function<void(int)> f;
    f = [](int a){ REQUIRE_EQ(a, 194); };
    REQUIRE(f);
    f(194);
}

TEST(function, can_assign_capturing_lambda) {
    function<void(int)> f;
    auto i = 9382;
    f = [&](int a){ REQUIRE_EQ(i, 9382); REQUIRE_EQ(a, 194); };
    REQUIRE(f);
    f(194);
}

namespace {

function<int(int)> get_function() {
    return [](int a){ return a; };
}

void call_function(function<char(char)> f) {
    auto result = f('c');
    REQUIRE_EQ(result, 'c');
}

} // namespace

TEST(function, can_be_returned_from_function) {
    function<int(int)> fn;
    fn = get_function();
    auto result = fn(201);
    REQUIRE_EQ(result, 201);
}

TEST(function, can_be_passed_to_function) {
    call_function([](char c){ return c; });
}

