#pragma once

#include <stddef.h>

// Alloc-free double-linked list based on the Linux kernel list implementation

namespace yacppl {

template <class Type>
class kernel_list final {

    kernel_list *_next = this, *_prev = this;
    size_t _offset;

    void add_element(kernel_list *new_element, kernel_list *prev, kernel_list *next) {
        next->_prev = new_element;
        prev->_next = new_element;
        new_element->_next = next;
        new_element->_prev = prev;
    }

    template <typename T, typename U>
    constexpr size_t offset_of(U T::*member) const {
        return reinterpret_cast<char *>(&(static_cast<T *>(nullptr)->*member)) - static_cast<char *>(nullptr);
    }

    Type *this_offset(int offset) {
        return reinterpret_cast<Type *>(reinterpret_cast<char *>(this) + offset);
    }

public:

    class iterator {

        kernel_list *ptr = nullptr;

    public:

        iterator(kernel_list *p)
            : ptr(p) {}

        iterator &operator++() {
            ptr = ptr->_next;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ptr = ptr->_next;
            return tmp;
        }

        iterator &operator--() {
            ptr = ptr->_prev;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            ptr = ptr->_prev;
            return tmp;
        }

        Type &operator *() {
            return *ptr->entry();
        }

        Type *operator->() {
            return ptr->entry();
        }

        bool operator==(const iterator &i) const {
            return i.ptr == ptr;
        }

        bool operator!=(const iterator &i) const {
            return i.ptr != ptr;
        }

    };

    template <typename U>
    explicit kernel_list(U Type::*member) {
        _offset = offset_of(member);
    }

    void add(kernel_list *new_element) {
        add_element(new_element, _prev, this);
    }

    void add_front(kernel_list *new_element) {
        add_element(new_element, this, _next);
    }

    void remove() {
        _next->_prev = _prev;
        _prev->_next = _next;
        _prev = _next = this;
    }

    bool empty() const {
        return (_prev == this) && (_next == this);
    }

    Type *entry() {
        return this_offset(-_offset);
    }

    Type *next_entry() {
        return _next == this ? nullptr : _next->entry();
    }

    iterator begin() {
        return iterator(_next);
    }

    iterator end() {
        return iterator(this);
    }

};

} // namespace yacppl

