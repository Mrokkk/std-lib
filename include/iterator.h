#pragma once

#include <cstddef>
#include "types.h"

namespace yacppl {

template <typename Container>
inline auto begin(Container &c) -> decltype (c.begin()) {
    return c.begin();
}

template <typename Container>
inline auto cbegin(const Container &c) -> decltype (c.cbegin()) {
    return c.cbegin();
}

template <typename Container>
inline auto end(Container &c) -> decltype (c.end()) {
    return c.end();
}

template <typename Container>
inline auto cend(const Container &c) -> decltype (c.cend()) {
    return c.cend();
}

inline char *begin(char *c) {
    return c;
}

inline const char *cbegin(const char *c) {
    return c;
}

inline size_t length(const char *string) {
    const char *temp;
    for (temp = string; *temp != 0; ++temp);
    return temp-string;
}

inline char *end(char *c) {
    return begin(c) + length(c);
}

inline const char *cend(const char *c) {
    return cbegin(c) + length(c);
}

template <class Array, size_t Size>
Array *begin(Array (&array)[Size]) {
    return array;
}

template <class Array, size_t Size>
const Array *cbegin(const Array (&array)[Size]) {
    return array;
}

template <class Array, size_t Size>
Array *end(Array (&array)[Size]) {
    return array + Size;
}

template <class Array, size_t Size>
const Array *cend(const Array (&array)[Size]) {
    return array + Size;
}

struct forward_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <typename value_type, bool is_const>
struct pointer_iterator {

    using reference = typename conditional<is_const, const value_type &, value_type &>::type;
    using pointer = typename conditional<is_const, const value_type *, value_type *>::type;
    using node_pointer = pointer;

private:

    pointer ptr_ = nullptr;

public:

    pointer_iterator() = default;

    pointer_iterator(pointer ptr) : ptr_(ptr) {
    }

    pointer_iterator(const pointer_iterator<value_type, false> &it) : ptr_(it.get()) {
    }

    pointer_iterator(const pointer_iterator<value_type, true> &it) : ptr_(it.get()) {
    }

    pointer_iterator &operator++() {
        ++ptr_;
        return *this;
    }

    pointer_iterator operator+(int i) const {
        return ptr_ + i;
    }

    pointer_iterator operator++(int) {
        auto tmp = *this;
        ++ptr_;
        return tmp;
    }

    pointer_iterator &operator--() {
        --ptr_;
        return *this;
    }

    pointer_iterator operator--(int) {
        auto tmp = *this;
        --ptr_;
        return tmp;
    }

    reference operator*() {
        return *ptr_;
    }

    pointer operator->() {
        return ptr_;
    }

    pointer get() {
        return ptr_;
    }

    const pointer get() const {
        return ptr_;
    }

    size_t operator-(const pointer_iterator &rhs) const {
        return ptr_ - rhs.ptr_;
    }

    pointer_iterator operator-(int i) const {
        return ptr_ - i;
    }

    bool operator==(const pointer &p) const {
        return ptr_ == const_cast<pointer>(p);
    }

    bool operator==(const pointer_iterator<value_type, true> &element) const {
        return ptr_ == const_cast<pointer>(element.get());
    }

    bool operator==(const pointer_iterator<value_type, false> &element) const {
        return ptr_ == const_cast<pointer>(element.get());
    }

    bool operator!=(const pointer &p) const {
        return ptr_ != const_cast<pointer>(p);
    }

    bool operator!=(const pointer_iterator<value_type, true> &element) const {
        return ptr_ != const_cast<pointer>(element.get());
    }

    bool operator!=(const pointer_iterator<value_type, false> &element) const {
        return ptr_ != const_cast<pointer>(element.get());
    }

};

template <typename list_type, typename iterator_tag, typename value_type, typename node_type, bool is_const>
struct list_iterator {

    using node_pointer = typename conditional<is_const, const node_type *, node_type *>::type;
    using reference = typename conditional<is_const, const value_type &, value_type &>::type;
    using pointer = typename conditional<is_const, const value_type *, value_type *>::type;

private:

    friend list_type;

    node_pointer ptr_ = nullptr;

    node_pointer node() {
        return ptr_;
    }

    const node_pointer node() const {
        return ptr_;
    }

public:

    list_iterator() = default;

    list_iterator(node_pointer p) : ptr_(p) {
    }

    list_iterator(const list_iterator<list_type, iterator_tag, value_type, node_pointer, false> &it)
            : ptr_(const_cast<node_pointer>(it.node())) {
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, forward_iterator_tag>::value || is_same<U, bidirectional_iterator_tag>::value,
        list_iterator
    >::type &operator++() {
        ptr_ = ptr_->next();
        return *this;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, forward_iterator_tag>::value || is_same<U, bidirectional_iterator_tag>::value,
        list_iterator
    >::type operator++(int) {
        auto tmp = *this;
        ptr_ = ptr_->next();
        return tmp;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, bidirectional_iterator_tag>::value, list_iterator
    >::type &operator--() {
        ptr_ = ptr_->prev();
        return *this;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, bidirectional_iterator_tag>::value, list_iterator
    >::type operator--(int) {
        auto tmp = *this;
        ptr_ = ptr_->prev();
        return tmp;
    }

    reference operator*() {
        return *ptr_->entry();
    }

    pointer operator->() {
        return ptr_->entry();
    }

    bool operator==(const node_pointer &p) const {
        return ptr_ == const_cast<const node_type *>(p);
    }

    bool operator==(const list_iterator<list_type, iterator_tag, value_type, node_type, true> &i) const {
        return ptr_ == const_cast<const node_type *>(i.node());
    }

    bool operator==(const list_iterator<list_type, iterator_tag, value_type, node_type, false> &i) const {
        return ptr_ == const_cast<node_type *>(i.node());
    }

    bool operator!=(const node_pointer &p) const {
        return ptr_ != const_cast<const node_type *>(p);
    }

    bool operator!=(const list_iterator<list_type, iterator_tag, value_type, node_type, true> &i) const {
        return ptr_ != const_cast<const node_type *>(i.node());
    }

    bool operator!=(const list_iterator<list_type, iterator_tag, value_type, node_type, false> &i) const {
        return ptr_ != const_cast<node_type *>(i.node());
    }

    friend class list_iterator<list_type, iterator_tag, value_type, node_type, false>;
    friend class list_iterator<list_type, iterator_tag, value_type, node_type, true>;

};

} // namespace yacppl

