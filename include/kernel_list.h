#pragma once

#include <stddef.h>
#include "types.h"

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

    template <bool is_const>
    struct detail_iterator {

        using value_type = Type;
        using reference = typename conditional<is_const, const value_type &, value_type &>::type;
        using pointer = typename conditional<is_const, const value_type *, value_type *>::type;

    private:

        kernel_list *ptr = nullptr;

    public:

        detail_iterator() = default;

        detail_iterator(kernel_list *p) : ptr(p) {
        }

        detail_iterator(const detail_iterator<true> &it) : ptr(it.ptr) {
        }

        detail_iterator(const detail_iterator<false> &it) : ptr(it.ptr) {
        }

        detail_iterator &operator++() {
            ptr = ptr->next_;
            return *this;
        }

        detail_iterator operator++(int) {
            auto tmp = *this;
            ptr = ptr->next_;
            return tmp;
        }

        detail_iterator &operator--() {
            ptr = ptr->prev_;
            return *this;
        }

        detail_iterator operator--(int) {
            auto tmp = *this;
            ptr = ptr->prev_;
            return tmp;
        }

        reference operator *() {
            return *ptr->entry();
        }

        pointer operator->() {
            return ptr->entry();
        }

        bool operator==(const detail_iterator &i) const {
            return i.ptr == ptr;
        }

        bool operator!=(const detail_iterator &i) const {
            return i.ptr != ptr;
        }

        friend struct detail_iterator<true>;

    };

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

};

} // namespace yacppl

