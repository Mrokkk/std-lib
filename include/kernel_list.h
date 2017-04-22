#pragma once

#include <stddef.h>

// Alloc-free double-linked list based on the Linux kernel list implementation

namespace yacppl {

template <class Type>
class kernel_list final {

    kernel_list *next_ = this, *prev_ = this;
    size_t offset_;

    void add_element(kernel_list *new_element, kernel_list *prev, kernel_list *next) {
        next->prev_ = new_element;
        prev->next_ = new_element;
        new_element->next_ = next;
        new_element->prev_ = prev;
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
            ptr = ptr->next_;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ptr = ptr->next_;
            return tmp;
        }

        iterator &operator--() {
            ptr = ptr->prev_;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            ptr = ptr->prev_;
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
        offset_ = offset_of(member);
    }

    void push_back(kernel_list *new_element) {
        add_element(new_element, prev_, this);
    }

    void push_front(kernel_list *new_element) {
        add_element(new_element, this, next_);
    }

    void remove() {
        next_->prev_ = prev_;
        prev_->next_ = next_;
        prev_ = next_ = this;
    }

    bool empty() const {
        return (prev_ == this) && (next_ == this);
    }

    Type *entry() {
        return this_offset(-offset_);
    }

    Type *next_entry() {
        return next_ == this ? nullptr : next_->entry();
    }

    iterator begin() {
        return iterator(next_);
    }

    iterator end() {
        return iterator(this);
    }

};

} // namespace yacppl

