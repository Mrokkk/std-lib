#pragma once

#include <stddef.h>
#include "iterator.h"

// Alloc-free double-linked list based on the Linux kernel list implementation

namespace yacppl {

template <typename Type>
class kernel_list final {

    kernel_list *next_ = this, *prev_ = this;
    size_t offset_;

    void add_node(kernel_list *new_node, kernel_list *prev, kernel_list *next) {
        next->prev_ = new_node;
        prev->next_ = new_node;
        new_node->next_ = next;
        new_node->prev_ = prev;
    }

    void remove_node(kernel_list *node) {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
        node->prev_ = node->next_ = node;
    }

    template <typename T, typename U>
    constexpr size_t offset_of(U T::*member) const {
        return reinterpret_cast<char *>(&(static_cast<T *>(nullptr)->*member)) - static_cast<char *>(nullptr);
    }

    kernel_list *list_member(Type *obj) {
        return reinterpret_cast<kernel_list *>(reinterpret_cast<char *>(obj) + offset_);
    }

    Type *this_offset(int offset) {
        return reinterpret_cast<Type *>(reinterpret_cast<char *>(this) + offset);
    }

    const Type *this_offset(int offset) const {
        return reinterpret_cast<const Type *>(reinterpret_cast<const char *>(this) + offset);
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

    kernel_list &push_back(Type &new_node) {
        add_node(list_member(&new_node), prev_, this);
        return *this;
    }

    kernel_list &push_front(Type &new_node) {
        add_node(list_member(&new_node), this, next_);
        return *this;
    }

    kernel_list &insert(const iterator &pos, Type &node) {
        add_node(list_member(&node), pos.node()->prev_, pos.node());
        return *this;
    }

    kernel_list &insert(Type &pos, Type &node) {
        auto node_member = list_member(&pos);
        add_node(list_member(&node), node_member->prev_, node_member);
        return *this;
    }

    kernel_list &erase(const iterator &it) {
        remove_node(it.node());
        return *this;
    }

    kernel_list &erase(Type &node) {
        remove_node(list_member(&node));
        return *this;
    }

    bool empty() const {
        return prev_ == this;
    }

    Type *entry() {
        return this_offset(-offset_);
    }

    const Type *entry() const {
        return this_offset(-offset_);
    }

    Type *next_entry() {
        return next_ == this ? nullptr : next_->entry();
    }

    Type *prev_entry() {
        return prev_ == this ? nullptr : prev_->entry();
    }

    iterator begin() {
        return iterator(next_);
    }

    const_iterator begin() const {
        return const_iterator(next_);
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

    const_iterator end() const {
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

