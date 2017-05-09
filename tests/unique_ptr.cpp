#include <unique_ptr.hpp>
#include <move.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(unique_ptr, can_create_empty_pointer) {
    unique_ptr<int> ptr;
    REQUIRE_EQ(ptr.get(), nullptr);
}

TEST(unique_ptr, can_create_valid_pointer) {
    unique_ptr<int> ptr(new int(4));
    REQUIRE_EQ(*ptr, 4);
}

TEST(unique_ptr, can_be_assigned) {
    unique_ptr<int> ptr;
    ptr = make_unique<int>(5);
    REQUIRE_EQ(*ptr, 5);
}

TEST(unique_ptr, can_be_moved) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2;
    ptr2 = move(ptr1);
    REQUIRE_EQ(*ptr2, 10);
    REQUIRE_EQ(ptr1.get(), nullptr);
}

TEST(unique_ptr, can_be_constructed_by_moving) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2(move(ptr1));
    REQUIRE_EQ(*ptr2, 10);
    REQUIRE_EQ(ptr1.get(), nullptr);
}

TEST(unique_ptr, can_be_casted_to_raw_pointer) {
    auto ptr = make_unique(10);
    int *raw_ptr = ptr;
    REQUIRE_EQ(*ptr, 10);
    REQUIRE_EQ(*raw_ptr, 10);
    REQUIRE_EQ(ptr.get(), raw_ptr);
}

TEST(unique_ptr, can_have_its_value_modified) {
    auto ptr = make_unique(10);
    *ptr = 39;
    REQUIRE_EQ(*ptr, 39);
}

namespace {

struct helper {
    int a;
    explicit helper(int a) : a(a) {}
};

template <typename Type>
void test_with_type() {
    unique_ptr<Type> ptr1;
    REQUIRE_FALSE(ptr1);
    ptr1 = new Type();
    REQUIRE(ptr1);
    REQUIRE_EQ(*ptr1, Type());
    ptr1 = nullptr;
    REQUIRE_FALSE(ptr1);
    unique_ptr<Type> ptr2(move(ptr1));
    REQUIRE_FALSE(ptr1);
    REQUIRE_FALSE(ptr2);
    ptr1 = new Type();
    ptr2 = move(ptr1);
    REQUIRE_FALSE(ptr1);
    REQUIRE(ptr2);
}

} // namespace anon

TEST(unique_ptr, can_work_with_struct) {
    for (auto i = 0; i < 1024; i++) {
        auto ptr = make_unique<helper>(i);
        REQUIRE_EQ(ptr->a, i);
    }
}

TEST(unique_ptr, works_with_simple_types) {
    test_with_type<char>();
    test_with_type<signed char>();
    test_with_type<unsigned char>();
    test_with_type<short>();
    test_with_type<unsigned short>();
    test_with_type<int>();
    test_with_type<unsigned int>();
    test_with_type<long>();
    test_with_type<long long>();
}

