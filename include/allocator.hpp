#pragma once

#include "kernel_list.hpp"
#include <cstddef>
#include <cstdint>

namespace yacppl {

template <class BackendAllocator, size_t _memory_block_size>
class allocator final {

    class memory_block {

        struct _data {
            unsigned char data[_memory_block_size];
            unsigned int block_ptr[0];
        } __attribute__((packed));

        template <typename Ptr>
        Ptr pointer_offset(Ptr ptr, int off) {
            return reinterpret_cast<Ptr>(reinterpret_cast<char *>(ptr) + off);
        }

    public:

        typename kernel_list<memory_block>::node list_;
        uint32_t size;
        bool free = false;

        constexpr explicit memory_block(size_t s)
            : size(s), free(false) {
        }

        void divide(size_t pivot) {
            auto old_size = size;
            size = pivot;
            free = false;
            auto new_block = reinterpret_cast<memory_block *>(pointer_offset(data(), pivot));
            new_block->size = old_size - _memory_block_size - size;
            new_block->free = true;
            list_.insert(&new_block->list_);
        }

        void try_to_divide(size_t pivot) {
            if (size <= pivot + 2 * _memory_block_size)
                free = false;
            else
                divide(pivot);
        }

        void *data() {
            return reinterpret_cast<_data *>(this)->block_ptr;
        }

        constexpr void *operator new(size_t, void *address) {
            return address;
        }

    };

    kernel_list<memory_block> blocks_;
    BackendAllocator backend_allocator_;

    void adapt_size(size_t &size) const {
        if (size % _memory_block_size)
            size = (size / _memory_block_size) * _memory_block_size + _memory_block_size;
    }

    memory_block *create_memory_block(size_t size) {
        return new(backend_allocator_.grow_heap(_memory_block_size + size)) memory_block(size);
    }

public:

    constexpr explicit allocator(char *heap_start)
        : blocks_(&memory_block::list_), backend_allocator_(heap_start) {}

    void *allocate(size_t size) {
        adapt_size(size);
        for (auto &temp : blocks_) {
            if (temp.free && temp.size >= size) {
                temp.try_to_divide(size);
                return temp.data();
            }
        }
        auto new_block = create_memory_block(size);
        if (new_block == nullptr) return nullptr;
        blocks_.push_back(*new_block);
        return new_block->data();
    }

    bool free(void *address) {
        for (auto &temp : blocks_) {
            if (temp.data() == address) {
                temp.free = true;
                return true;
            }
            auto next = temp.list_.next()->entry();
            if (!next) break;
            if (next->free && temp.free) {
                temp.size = temp.size + next->size + _memory_block_size;
                blocks_.erase(*next);
            }
        }
        return false;
    }

};

} // namespace yacppl

