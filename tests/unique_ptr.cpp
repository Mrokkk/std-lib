#include <unique_ptr.h>
#include <move.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(unique_ptr, can_create_empty_pointer) {
    unique_ptr<int> ptr;
    REQUIRE(ptr.get() ==  (void *) NULL);
}

TEST(unique_ptr, can_create_valid_pointer) {
    unique_ptr<int> ptr(new int(4));
    REQUIRE(*ptr ==  4);
}

TEST(unique_ptr, can_be_assigned) {
    unique_ptr<int> ptr;
    ptr = make_unique<int>(5);
    REQUIRE(*ptr ==  5);
}

TEST(unique_ptr, can_be_moved) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2;
    ptr2 = move(ptr1);
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get() ==  (void *) NULL);
}

TEST(unique_ptr, can_be_constructed_by_moving) {
    auto ptr1 = make_unique<int>(10);
    unique_ptr<int> ptr2(move(ptr1));
    REQUIRE(*ptr2 ==  10);
    REQUIRE(ptr1.get() ==  (void *) NULL);
}

TEST(unique_ptr, can_be_casted_to_raw_pointer) {
    auto ptr = make_unique(10);
    int *raw_ptr = ptr;
    REQUIRE(*ptr ==  10);
    REQUIRE(*raw_ptr ==  10);
    REQUIRE(ptr.get() ==  raw_ptr);
}

TEST(unique_ptr, can_have_its_value_modified) {
    auto ptr = make_unique(10);
    *ptr = 39;
    REQUIRE(*ptr ==  39);
}

