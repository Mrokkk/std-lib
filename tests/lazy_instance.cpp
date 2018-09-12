#include <stddef.h>

inline constexpr void* operator new(size_t, void* address)
{
    return address;
}

#include <lazy_instance.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(lazy_instance, can_create_empty_instance)
{
    lazy_instance<int> instance;
    REQUIRE_FALSE(instance);
}

TEST(lazy_instance, can_be_initialized)
{
    lazy_instance<int> instance;
    instance.initialize(2);
    REQUIRE(instance);
    REQUIRE_EQ(*instance.get(), 2);
}

