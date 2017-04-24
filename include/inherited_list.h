#pragma once

#include "iterator.h"

namespace yacppl {

template <typename Type>
struct inherited_list {

    struct node {

        node *prev_, *next_;

        node() {
            next_ = prev_ = this;
        }

        node *next() {
            return next_ == this ? nullptr : next_;
        }

        const node *next() const {
            return next_ == this ? nullptr : next_;
        }

        node *prev() {
            return prev_ == this ? nullptr : prev_;
        }

        const node *prev() const {
            return prev_ == this ? nullptr : prev_;
        }

        Type *entry() {
            return reinterpret_cast<Type *>(this);
        }

        const Type *entry() const {
            return reinterpret_cast<const Type *>(this);
        }

    };

private:

    node head_;

    void add_element(node &new_element, node &prev, node &next) {
        next.prev_ = &new_element;
        prev.next_ = &new_element;
        new_element.next_ = &next;
        new_element.prev_ = &prev;
    }

    template <bool is_const>
    using detail_iterator = list_iterator<Type, node, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    constexpr inherited_list() = default;

    inherited_list &push_back(node *new_element) {
        add_element(*new_element, *head_.prev_, head_);
        return *this;
    }

    inherited_list &push_front(node *new_element) {
        add_element(*new_element, head_, *head_.next_);
        return *this;
    }

    inherited_list &erase(node &node) {
        node.next_->prev_ = node.prev_;
        node.prev_->next_ = node.next_;
        node.prev_ = node.next_ = &head_;
        return *this;
    }

    bool empty() const {
        return head_.next_ == &head_ && head_.next_ == &head_;
    }

    iterator begin() {
        return iterator(head_.next_);
    }

    const_iterator begin() const {
        return const_iterator(head_.next_);
    }

    iterator end() {
        return iterator(&head_);
    }

    const_iterator end() const {
        return const_iterator(&head_);
    }

    const_iterator cbegin() const {
        return const_iterator(head_.next_);
    }

    const_iterator cend() const {
        return const_iterator(head_);
    }

};

} // namespace yacppl

