#pragma once

#include <stddef.h>
#include "iterator.h"

// Alloc-free double-linked list based on the Linux kernel list implementation

namespace yacppl {

template <typename Type>
struct kernel_list final {

    class node {

        node *next_ = this, *prev_ = this;
        size_t offset_ = 0;

        Type *this_offset(int offset) {
            return reinterpret_cast<Type *>(reinterpret_cast<char *>(this) + offset);
        }

        const Type *this_offset(int offset) const {
            return reinterpret_cast<const Type *>(reinterpret_cast<const char *>(this) + offset);
        }

    public:

        node() = default;

        node *&next() {
            return next_;
        }

        node *&prev() {
            return prev_;
        }

        const node *next() const {
            return next_;
        }

        const node *prev() const {
            return prev_;
        }

        Type *entry() {
            return this_offset(-offset_);
        }

        const Type *entry() const {
            return this_offset(-offset_);
        }

        void set_offset(size_t offset) {
            offset_ = offset;
        }

        // FIXME: remove
        void insert(node *new_node) {
            new_node->set_offset(offset_);
            next_->prev() = new_node;
            prev_->next() = new_node;
            new_node->next() = next_;
            new_node->prev() = prev_;
        }

    };

private:

    node head_;
    size_t offset_;

    void add_node(node *new_node, node *prev, node *next) {
        new_node->set_offset(offset_);
        next->prev() = new_node;
        prev->next() = new_node;
        new_node->next() = next;
        new_node->prev() = prev;
    }

    void remove_node(node *n) {
        n->next()->prev() = n->prev();
        n->prev()->next() = n->next();
        n->prev() = n->next() = n;
    }

    template <typename T, typename U>
    constexpr size_t offset_of(U T::*member) const {
        return reinterpret_cast<char *>(&(static_cast<T *>(nullptr)->*member)) - static_cast<char *>(nullptr);
    }

    node *list_member(Type *obj) {
        return reinterpret_cast<node *>(reinterpret_cast<char *>(obj) + offset_);
    }

    template <bool is_const>
    using detail_iterator = list_iterator<Type, node, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    template <typename U>
    constexpr explicit kernel_list(U Type::*member) {
        offset_ = offset_of(member);
    }

    kernel_list &push_back(Type &new_node) {
        add_node(list_member(&new_node), head_.prev(), &head_);
        return *this;
    }

    kernel_list &push_front(Type &new_node) {
        add_node(list_member(&new_node), &head_, head_.next());
        return *this;
    }

    kernel_list &insert(const iterator &pos, Type &new_node) {
        add_node(list_member(&new_node), pos.node()->prev(), pos.node());
        return *this;
    }

    kernel_list &insert(Type &pos, Type &new_node) {
        auto node_member = list_member(&pos);
        add_node(list_member(&new_node), node_member->prev(), node_member);
        return *this;
    }

    kernel_list &erase(const iterator &it) {
        remove_node(it.node());
        return *this;
    }

    kernel_list &erase(Type &n) {
        remove_node(list_member(&n));
        return *this;
    }

    bool empty() const {
        return head_.prev() == &head_;
    }

    iterator begin() {
        return iterator(head_.next());
    }

    const_iterator begin() const {
        return const_iterator(head_.next());
    }

    const_iterator cbegin() const {
        return const_iterator(head_.next());
    }

    iterator end() {
        return iterator(&head_);
    }

    const_iterator cend() const {
        return const_iterator(&head_);
    }

    const_iterator end() const {
        return const_iterator(&head_);
    }

};

} // namespace yacppl

