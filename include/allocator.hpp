#pragma once

#include <cstddef>
#include <cstdint>
#include "spinlock.hpp"
#include "kernel_list.hpp"

namespace yacppl
{

template <class BackendAllocator, size_t MemoryBlockSize>
class allocator final
{
    struct memory_block;

public:
    constexpr explicit allocator(char* heap_start)
        : blocks_(&memory_block::list_)
        , backend_allocator_(heap_start)
    {
    }

    void* allocate(size_t size)
    {
        adapt_size(size);
        auto _ = make_scoped_lock(spinlock_);
        for (auto& temp : blocks_)
        {
            if (temp.free and temp.size >= size)
            {
                temp.try_to_divide(size);
                return temp.data();
            }
        }
        auto new_block = create_memory_block(size);
        if (new_block == nullptr) return nullptr;
        blocks_.push_back(*new_block);
        return new_block->data();
    }

    bool free(void* address)
    {
        auto _ = make_scoped_lock(spinlock_);
        for (auto& temp : blocks_)
        {
            if (temp.data() == address)
            {
                temp.free = true;
                return true;
            }
            auto next = temp.list_.next()->entry();
            if (not next)
            {
                break;
            }
            if (next->free and temp.free)
            {
                temp.size = temp.size + next->size + MemoryBlockSize;
                blocks_.erase(*next);
            }
        }
        return false;
    }

private:
    struct memory_block final
    {
        constexpr explicit memory_block(const size_t s)
            : size(s), free(false)
        {
        }

        void divide(const size_t pivot)
        {
            auto old_size = size;
            size = pivot;
            free = false;
            auto new_block = reinterpret_cast<memory_block*>(pointer_offset(data(), pivot));
            new_block->size = old_size - MemoryBlockSize - size;
            new_block->free = true;
            list_.insert(&new_block->list_);
        }

        void try_to_divide(const size_t pivot)
        {
            if (size <= pivot + 2 * MemoryBlockSize)
                free = false;
            else
                divide(pivot);
        }

        void* data()
        {
            return reinterpret_cast<_data*>(this)->block_ptr;
        }

        constexpr void* operator new(size_t, void* address)
        {
            return address;
        }

        typename kernel_list<memory_block>::node list_;
        uint32_t size;
        bool free = false;

    private:
        struct _data
        {
            uint8_t data[MemoryBlockSize];
            uint8_t block_ptr[0];
        } __attribute__((packed));

        template <typename Ptr>
        Ptr pointer_offset(Ptr ptr, const int off)
        {
            return reinterpret_cast<Ptr>(reinterpret_cast<char*>(ptr) + off);
        }
    };

    void adapt_size(size_t& size) const
    {
        if (size % MemoryBlockSize)
        {
            size = (size / MemoryBlockSize) * MemoryBlockSize + MemoryBlockSize;
        }
    }

    memory_block* create_memory_block(const size_t size)
    {
        return new(backend_allocator_.grow_heap(MemoryBlockSize + size)) memory_block(size);
    }

    kernel_list<memory_block> blocks_;
    BackendAllocator backend_allocator_;
    static spinlock spinlock_;
};

template <class BackendAllocator, size_t MemoryBlockSize>
spinlock allocator<BackendAllocator, MemoryBlockSize>::spinlock_;

} // namespace yacppl
