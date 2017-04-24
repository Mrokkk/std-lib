#pragma once

#include "iterator.h"

namespace yacppl {

template <typename Type>
class inherited_list {

    Type *prev_, *next_;

    void add_element(Type &new_element, Type &prev, Type &next) {
        next.prev_ = &new_element;
        prev.next_ = &new_element;
        new_element.next_ = &next;
        new_element.prev_ = &prev;
    }

    operator Type &() {
        return *reinterpret_cast<Type *>(this);
    }

    template <bool is_const>
    using detail_iterator = list_iterator<Type, Type, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    constexpr inherited_list() {
        next_ = prev_ = reinterpret_cast<Type *>(this);
    }

    Type &push_back(Type *new_element) {
        add_element(*new_element, *prev_, *this);
        return *this;
    }

    Type &push_front(Type *new_element) {
        add_element(*new_element, *this, *next_);
        return *this;
    }

    Type &remove() {
        next_->prev_ = prev_;
        prev_->next_ = next_;
        prev_ = next_ = reinterpret_cast<Type *>(this);
        return *prev_;
    }

    Type *next() {
        return next_ == this ? nullptr : next_;
    }

    Type *prev() {
        return prev_ == this ? nullptr : prev_;
    }

    Type *entry() {
        return reinterpret_cast<Type *>(this);
    }

    bool empty() const {
        return next_ == this && next_ == this;
    }

    iterator begin() {
        return iterator(next_);
    }

    const_iterator begin() const {
        return const_iterator(next_);
    }

    iterator end() {
        return iterator(reinterpret_cast<Type *>(this));
    }

    const_iterator end() const {
        return const_iterator(reinterpret_cast<const Type *>(this));
    }

    const_iterator cbegin() const {
        return const_iterator(next_);
    }

    const_iterator cend() const {
        return const_iterator(reinterpret_cast<const Type *>(this));
    }

};

} // namespace yacppl

