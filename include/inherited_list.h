#pragma once

#include "iterator.h"

namespace yacppl {

template <typename Type>
struct inherited_list {

    class node {

        node *prev_ = this, *next_ = this;

    public:

        node() = default;

        node *&next() {
            return next_;
        }

        const node *next() const {
            return next_;
        }

        node *&prev() {
            return prev_;
        }

        const node *prev() const {
            return prev_;
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
        next.prev() = &new_element;
        prev.next() = &new_element;
        new_element.next() = &next;
        new_element.prev() = &prev;
    }

    template <bool is_const>
    using detail_iterator = list_iterator<inherited_list, bidirectional_iterator_tag, Type, node, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    inherited_list() = default;

    inherited_list &push_back(node &new_element) {
        add_element(new_element, *head_.prev(), head_);
        return *this;
    }

    inherited_list &push_front(node &new_element) {
        add_element(new_element, head_, *head_.next());
        return *this;
    }

    // FIXME: inserting at begin()
    inherited_list &insert(const iterator &it, node &new_element) {
        add_element(new_element, *it.node()->prev(), *it.node());
        return *this;
    }

    inherited_list &erase(node &node) {
        node.next()->prev() = node.prev();
        node.prev()->next() = node.next();
        node.prev() = node.next() = &node;
        return *this;
    }

    inherited_list &erase(const iterator &it) {
        it.node()->next()->prev() = it.node()->prev();
        it.node()->prev()->next() = it.node()->next();
        it.node()->prev() = it.node()->next() = it.node();
        return *this;
    }

    bool empty() const {
        return head_.next() == &head_;
    }

    iterator begin() {
        return iterator(head_.next());
    }

    const_iterator begin() const {
        return const_iterator(head_.next());
    }

    iterator end() {
        return iterator(&head_);
    }

    const_iterator end() const {
        return const_iterator(&head_);
    }

    const_iterator cbegin() const {
        return const_iterator(head_.next());
    }

    const_iterator cend() const {
        return const_iterator(&head_);
    }

};

} // namespace yacppl

