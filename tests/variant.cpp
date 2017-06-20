#include <new>
#include <variant.hpp>
#include "yatf/include/yatf.hpp"

#include <string.hpp>

using namespace yacppl;

struct helper {
    int a, b, c;
};

TEST(variant, can_be_created_empty) {
    variant<int> v1;
    REQUIRE_EQ(v1.safe_get<int>(), nullptr);
    variant<int, char> v2;
    REQUIRE_EQ(v2.safe_get<int>(), nullptr);
    REQUIRE_EQ(v2.safe_get<char>(), nullptr);
    variant<int, char, helper> v3;
    REQUIRE_EQ(v3.safe_get<int>(), nullptr);
    REQUIRE_EQ(v3.safe_get<char>(), nullptr);
    REQUIRE_EQ(v3.safe_get<helper>(), nullptr);
}

TEST(variant, can_be_created_from_value) {
    variant<int, char, helper> v1(32);
    REQUIRE_EQ(v1.get<int>(), 32);
    REQUIRE(v1.safe_get<int>() != nullptr);
    REQUIRE(v1.safe_get<char>() == nullptr);
    REQUIRE(v1.safe_get<helper>() == nullptr);
    variant<int, char, helper> v2('c');
    REQUIRE_EQ(v2.get<char>(), 'c');
    REQUIRE(v2.safe_get<int>() == nullptr);
    REQUIRE(v2.safe_get<char>() != nullptr);
    REQUIRE(v2.safe_get<helper>() == nullptr);
    variant<int, char, helper> v3(helper{1, 2, 3});
    REQUIRE_EQ(v3.get<helper>().a, 1);
    REQUIRE_EQ(v3.get<helper>().b, 2);
    REQUIRE_EQ(v3.get<helper>().c, 3);
    REQUIRE(v3.safe_get<int>() == nullptr);
    REQUIRE(v3.safe_get<char>() == nullptr);
    REQUIRE(v3.safe_get<helper>() != nullptr);
}

TEST(variant, can_be_set) {
    variant<int, char, helper> v;
    v.set<int>(-921);
    REQUIRE_EQ(v.get<int>(), -921);
    REQUIRE(v.safe_get<int>() != nullptr);
    REQUIRE(v.safe_get<char>() == nullptr);
    REQUIRE(v.safe_get<helper>() == nullptr);
    v.set<char>('f');
    REQUIRE_EQ(v.get<char>(), 'f');
    REQUIRE(v.safe_get<int>() == nullptr);
    REQUIRE(v.safe_get<char>() != nullptr);
    REQUIRE(v.safe_get<helper>() == nullptr);
    v.set<helper>(helper{1, 2, 4});
    REQUIRE_EQ(v.get<helper>().a, 1);
    REQUIRE_EQ(v.get<helper>().b, 2);
    REQUIRE_EQ(v.get<helper>().c, 4);
    REQUIRE(v.safe_get<int>() == nullptr);
    REQUIRE(v.safe_get<char>() == nullptr);
    REQUIRE(v.safe_get<helper>() != nullptr);
}

TEST(variant, can_be_assigned) {
    variant<int, char, helper> v;
    v = -921;
    REQUIRE_EQ(v.get<int>(), -921);
    REQUIRE(v.safe_get<int>() != nullptr);
    REQUIRE(v.safe_get<char>() == nullptr);
    REQUIRE(v.safe_get<helper>() == nullptr);
    v = 'f';
    REQUIRE_EQ(v.get<char>(), 'f');
    REQUIRE(v.safe_get<int>() == nullptr);
    REQUIRE(v.safe_get<char>() != nullptr);
    REQUIRE(v.safe_get<helper>() == nullptr);
    v = helper{1, 2, 4};
    REQUIRE_EQ(v.get<helper>().a, 1);
    REQUIRE_EQ(v.get<helper>().b, 2);
    REQUIRE_EQ(v.get<helper>().c, 4);
    REQUIRE(v.safe_get<int>() == nullptr);
    REQUIRE(v.safe_get<char>() == nullptr);
    REQUIRE(v.safe_get<helper>() != nullptr);
}

struct allocating_helper {

    allocating_helper() : data(new int()) {
    }

    ~allocating_helper() {
        if (data != nullptr) {
            delete data;
        }
    }

    allocating_helper(const allocating_helper &) : data(new int()) {
    }

    allocating_helper(allocating_helper &&h) : data(h.data) {
    }

    int *data;

};

TEST(variant, does_not_leak_memory) {
    variant<int, allocating_helper> v(allocating_helper{});
    v = allocating_helper{};
    v = allocating_helper{};
}

