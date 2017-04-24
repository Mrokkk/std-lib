#pragma once

#include <stddef.h>
#include "iterator.h"

// Alloc-free double-linked list based on the Linux kernel list implementation

namespace yacppl {

template <typename Type>
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

    template <bool is_const>
    using detail_iterator = list_iterator<Type, kernel_list, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

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

    const_iterator cbegin() const {
        return const_iterator(next_);
    }

    iterator end() {
        return iterator(this);
    }

    const_iterator cend() const {
        return const_iterator(this);
    }

    kernel_list *next() const {
        return next_;
    }

    kernel_list *prev() const {
        return prev_;
    }

} __attribute__((packed));

} // namespace yacppl

