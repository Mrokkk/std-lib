#pragma once

#include "inherited_list.h"
#include <cstddef>

namespace yacppl {

template <class BackendAllocator, size_t _memory_block_size>
class allocator final {

    class memory_block : public inherited_list<memory_block> {

        struct _data {
            unsigned char data[_memory_block_size];
            unsigned int block_ptr[0];
        } __attribute__((packed));

        template <typename Ptr>
        Ptr pointer_offset(Ptr ptr, int off) {
            return reinterpret_cast<Ptr>(reinterpret_cast<char *>(ptr) + off);
        }

    public:

        size_t size;
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
            inherited_list<memory_block>::add_front(new_block);
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

    inherited_list<memory_block> _blocks;
    BackendAllocator _backend_allocator;

    void adapt_size(size_t &size) const {
        if (size % _memory_block_size)
            size = (size / _memory_block_size) * _memory_block_size + _memory_block_size;
    }

    memory_block *create_memory_block(size_t size) {
        return new(_backend_allocator.grow_heap(_memory_block_size + size)) memory_block(size);
    }

public:

    constexpr explicit allocator(char *heap_start)
        : _backend_allocator(heap_start) {}

    void *allocate(size_t size) {
        adapt_size(size);
        for (auto &temp : _blocks) {
            if (temp.free && temp.size >= size) {
                temp.try_to_divide(size);
                return temp.data();
            }
        }
        auto new_block = create_memory_block(size);
        if (new_block == nullptr) return nullptr;
        _blocks.add(new_block);
        return new_block->data();
    }

    bool free(void *address) {
        for (auto &temp : _blocks) {
            if (temp.data() == address) {
                temp.free = true;
                return true;
            }
            auto next = temp.next();
            if (!next) continue;
            if (next->free && temp.free) {
                temp.size = temp.size + next->size + _memory_block_size;
                next->remove();
            }
        }
        return false;
    }

};

} // namespace yacppl

