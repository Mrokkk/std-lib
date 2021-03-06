#include <shared_ptr.hpp>
#include <move.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(shared_ptr, can_create_empty_pointer) {
    shared_ptr<int> ptr;
    REQUIRE(ptr.get() ==  nullptr);
    REQUIRE(ptr.get_ref_count() == 0);
    shared_ptr<char> ptr2(nullptr);
    REQUIRE(ptr2.get() == nullptr);
    REQUIRE(ptr2.get_ref_count() == 0);
}

TEST(shared_ptr, can_create_valid_pointer) {
    shared_ptr<int> ptr(new int(4));
    REQUIRE(ptr.get() !=  nullptr);
}

TEST(shared_ptr, can_be_derefereced) {
    shared_ptr<int> ptr(new int(4));
    REQUIRE(*ptr ==  4);
}

TEST(shared_ptr, can_be_assigned) {
    shared_ptr<int> ptr;
    ptr = make_shared<int>(5);
    REQUIRE(*ptr ==  5);
    ptr = shared_ptr<int>();
    REQUIRE(ptr.get() == nullptr);
    REQUIRE_EQ(ptr.get_ref_count(), 0u);
    auto other_ptr = make_shared<int>(3);
    ptr = other_ptr;
    REQUIRE(ptr);
    REQUIRE_EQ(*ptr, 3);
    REQUIRE_EQ(ptr.get_ref_count(), 2u);
    REQUIRE_EQ(other_ptr.get_ref_count(), 2u);
    ptr = nullptr;
    REQUIRE_FALSE(ptr);
    REQUIRE_EQ(ptr.get_ref_count(), 0u);
    ptr = make_shared<int>(-214);
    REQUIRE(ptr);
    REQUIRE_EQ(*ptr, -214);
    REQUIRE_EQ(ptr.get_ref_count(), 1u);
}

TEST(shared_ptr, can_be_copied) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2;
    ptr2 = ptr1;
    REQUIRE(*ptr1 ==  10);
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get_ref_count() == 2);
    REQUIRE(ptr2.get_ref_count() == 2);
    REQUIRE(ptr1.get() ==  ptr2.get());
    {
        shared_ptr<int> ptr3;
        ptr3 = ptr2;
        REQUIRE(*ptr1 ==  10);
        REQUIRE(*ptr2 ==  10);
        REQUIRE(*ptr3 ==  10);
        REQUIRE(ptr1.get_ref_count() == 3);
        REQUIRE(ptr2.get_ref_count() == 3);
        REQUIRE(ptr2.get_ref_count() == 3);
        REQUIRE(ptr1.get() ==  ptr3.get());
    }
    REQUIRE(ptr1.get_ref_count() == 2);
    REQUIRE(ptr2.get_ref_count() == 2);
    REQUIRE(ptr1.get() ==  ptr2.get());
}

TEST(shared_ptr, can_be_moved) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2;
    ptr2 = move(ptr1);
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get() ==  nullptr);
    REQUIRE(ptr1.get_ref_count() == 0);
    REQUIRE(ptr2.get_ref_count() == 1);
    REQUIRE_FALSE(ptr1.get() ==  ptr2.get());
}

TEST(shared_ptr, can_be_constructed_by_copy) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2(ptr1);
    REQUIRE(*ptr1 ==  10);
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get_ref_count() == 2);
    REQUIRE(ptr2.get_ref_count() == 2);
    REQUIRE(ptr1.get() ==  ptr2.get());
}

TEST(shared_ptr, can_be_constructed_by_moving) {
    auto ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2 = move(ptr1);
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get() ==  nullptr);
    REQUIRE(ptr1.get_ref_count() == 0);
    REQUIRE(ptr2.get_ref_count() == 1);
    REQUIRE(ptr1.get() !=  ptr2.get());
}

TEST(shared_ptr, can_be_casted_to_raw_pointer) {
    auto ptr = make_shared<int>(10);
    int *raw_ptr = ptr;
    REQUIRE(*ptr ==  10);
    REQUIRE(*raw_ptr ==  10);
    REQUIRE(ptr.get() ==  raw_ptr);
}

TEST(shared_ptr, can_have_its_value_modified) {
    auto ptr = make_shared(10);
    *ptr = 39;
    REQUIRE(*ptr ==  39);
    REQUIRE(ptr.get_ref_count() == 1);
}

TEST(shared_ptr, can_be_reset) {
    auto ptr = make_shared(234);
    ptr.reset(new int());
    REQUIRE_EQ(*ptr, int());
    ptr.reset(nullptr);
    REQUIRE_FALSE(ptr);
    ptr.reset(make_shared(943));
    REQUIRE_EQ(*ptr, 943);
}

namespace {

struct helper {
    int a;
    explicit helper(int a) : a(a) {}
};

template <typename Type>
void test_with_type() {
    shared_ptr<Type> ptr1;
    REQUIRE_FALSE(ptr1);
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    ptr1 = make_shared<Type>();
    REQUIRE(ptr1);
    REQUIRE_EQ(ptr1.get_ref_count(), 1u);
    shared_ptr<Type> ptr2(ptr1);
    REQUIRE(ptr2);
    REQUIRE_EQ(ptr1.get_ref_count(), 2u);
    REQUIRE_EQ(ptr2.get_ref_count(), 2u);
    shared_ptr<Type> ptr3;
    ptr3 = ptr1;
    REQUIRE_EQ(ptr1.get_ref_count(), 3u);
    REQUIRE_EQ(ptr2.get_ref_count(), 3u);
    REQUIRE_EQ(ptr3.get_ref_count(), 3u);
    ptr3 = ptr2;
    REQUIRE_EQ(ptr1.get_ref_count(), 3u);
    REQUIRE_EQ(ptr2.get_ref_count(), 3u);
    REQUIRE_EQ(ptr3.get_ref_count(), 3u);
    ptr1 = nullptr;
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    REQUIRE_EQ(ptr2.get_ref_count(), 2u);
    REQUIRE_EQ(ptr3.get_ref_count(), 2u);
    shared_ptr<Type> ptr4;
    ptr2 = ptr4;
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    REQUIRE_EQ(ptr2.get_ref_count(), 0u);
    REQUIRE_EQ(ptr3.get_ref_count(), 1u);
    REQUIRE_EQ(ptr4.get_ref_count(), 0u);
    ptr4 = shared_ptr<Type>();
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    REQUIRE_EQ(ptr2.get_ref_count(), 0u);
    REQUIRE_EQ(ptr3.get_ref_count(), 1u);
    REQUIRE_EQ(ptr4.get_ref_count(), 0u);
    ptr3 = shared_ptr<Type>();
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    REQUIRE_EQ(ptr2.get_ref_count(), 0u);
    REQUIRE_EQ(ptr3.get_ref_count(), 0u);
    REQUIRE_EQ(ptr4.get_ref_count(), 0u);
    shared_ptr<Type> ptr5(ptr1);
    REQUIRE_FALSE(ptr5);
    REQUIRE_EQ(ptr1.get_ref_count(), 0u);
    REQUIRE_EQ(ptr2.get_ref_count(), 0u);
    REQUIRE_EQ(ptr3.get_ref_count(), 0u);
    REQUIRE_EQ(ptr4.get_ref_count(), 0u);
    REQUIRE_EQ(ptr5.get_ref_count(), 0u);
}

} // namespace anon

TEST(shared_ptr, can_work_with_struct) {
    for (auto i = 0; i < 1024; i++) {
        auto ptr = make_shared<helper>(i);
        REQUIRE_EQ(ptr->a, i);
    }
}

TEST(shared_ptr, works_with_simple_types) {
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

