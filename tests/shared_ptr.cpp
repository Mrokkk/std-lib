#include <shared_ptr.h>
#include <move.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(shared_ptr, can_create_empty_pointer) {
    shared_ptr<int> ptr;
    REQUIRE(ptr.get() ==  nullptr);
    REQUIRE(ptr.get_ref_count() == 0);
}

TEST(shared_ptr, can_create_valid_pointer) {
    shared_ptr<int> ptr(new int(4));
    REQUIRE_FALSE(ptr.get() ==  nullptr);
}

TEST(shared_ptr, can_be_derefereced) {
    shared_ptr<int> ptr(new int(4));
    REQUIRE(*ptr ==  4);
}

TEST(shared_ptr, can_be_assigned) {
    shared_ptr<int> ptr;
    ptr = make_shared<int>(5);
    REQUIRE(*ptr ==  5);
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
    REQUIRE_FALSE(ptr1.get() ==  ptr2.get());
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
