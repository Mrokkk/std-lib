#include <allocator.hpp>
#include "yatf/include/yatf.hpp"

struct heap_allocator final
{
    explicit heap_allocator(char* heap_start)
        : _heap(heap_start)
        {
    }

    void* grow_heap(size_t value)
    {
        auto prev_heap = _heap;
        _heap += value;
        return prev_heap;
    }

private:
    char* _heap = nullptr;
};

char allocator_test_map[1024 * 1024];

using namespace yacppl;

TEST(allocator, can_allocate)
{
    constexpr size_t memory_block_size = 32;
    auto expected = allocator_test_map + memory_block_size;
    allocator<heap_allocator, memory_block_size> test_allocator(allocator_test_map);
    for (auto i = 1; i < 1025; ++i)
    {
        auto result = test_allocator.allocate(i);
        REQUIRE(result == expected);
        *static_cast<unsigned int*>(result) = i;
        expected += memory_block_size * (2 + (i - 1) / memory_block_size);
    }
    for (unsigned int i = 1024; i > 0; --i)
    {
        expected -= memory_block_size * (2 + (i - 1) / memory_block_size);
        REQUIRE(*reinterpret_cast<unsigned int*>(expected) == i);
    }
}

TEST(allocator, cannot_free_invalid_ptr)
{
    constexpr size_t memory_block_size = 32;
    allocator<heap_allocator, memory_block_size> test_allocator(allocator_test_map);
    for (auto i = 0; i < 4096; ++i)
    {
        REQUIRE_FALSE(test_allocator.free(reinterpret_cast<void*>(i)));
    }
    for (auto i = 0; i < 100; ++i)
    {
        test_allocator.allocate(i);
    }
    for (auto i = 0; i < 4096; ++i)
    {
        REQUIRE_FALSE(test_allocator.free(reinterpret_cast<void*>(i)));
    }
}

TEST(allocator, can_divide_blocks)
{
    constexpr size_t memory_block_size = 32;
    allocator<heap_allocator, memory_block_size> test_allocator(allocator_test_map);
    auto data1 = test_allocator.allocate(120);
    auto expected = allocator_test_map + memory_block_size;
    REQUIRE(data1 == expected);
    test_allocator.free(data1);
    auto data2 = test_allocator.allocate(2);
    REQUIRE(data2 == expected);
    auto data3 = test_allocator.allocate(2);
    expected += memory_block_size * 2;
    REQUIRE(data3 == expected);
    auto data4 = test_allocator.allocate(2);
    expected += memory_block_size * 3; // dead memory area
    REQUIRE(data4 == expected);
    auto data5 = test_allocator.allocate(2);
    expected += memory_block_size * 2;
    REQUIRE(data5 == expected);
    auto data6 = test_allocator.allocate(2);
    expected += memory_block_size * 2;
    REQUIRE(data6 == expected);
}

TEST(allocator, can_merge_blocks)
{
    constexpr size_t memory_block_size = 32;
    allocator<heap_allocator, memory_block_size> alloc(allocator_test_map);
    auto data1 = alloc.allocate(1024);
    auto data2 = alloc.allocate(1024);
    auto data3 = alloc.allocate(1024);
    auto data4 = alloc.allocate(1024);
    REQUIRE(data1);
    REQUIRE(data2);
    REQUIRE(data3);
    REQUIRE(data4);
    alloc.free(data1);
    alloc.free(data2);
    alloc.free(data3);
    auto data5 = alloc.allocate(2 * 1024);
    REQUIRE_EQ(data1, data5);
}

