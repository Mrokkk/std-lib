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

namespace detail {

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value
>::type increment(node_pointer &n) {
    ++n;
}

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value
>::type decrement(node_pointer &n) {
    --n;
}

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value,
    value_pointer
>::type entry(node_pointer &n) {
    return n;
}

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    !is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value
>::type increment(node_pointer &n) {
    n = n->next();
}

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    !is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value
>::type decrement(node_pointer &n) {
    n = n->prev();
}

template <typename node_pointer, typename value_pointer>
inline typename enable_if<
    !is_same<
        typename remove_const<value_pointer>::type,
        typename remove_const<node_pointer>::type
    >::value,
    value_pointer
>::type entry(node_pointer &n) {
    return n->entry();
}

template <typename container_type, typename iterator_tag, bool is_const>
struct iterator {

    using node_type = typename container_type::node_type;
    using node_pointer = typename conditional<is_const, const node_type *, node_type *>::type;
    using value_type = typename container_type::value_type;
    using value_reference = typename conditional<is_const, const value_type &, value_type &>::type;
    using value_pointer = typename conditional<is_const, const value_type *, value_type *>::type;

private:

    friend container_type;

    node_pointer ptr_ = nullptr;

    node_pointer node() {
        return ptr_;
    }

    const node_pointer node() const {
        return ptr_;
    }

public:

    iterator() = default;

    iterator(const node_pointer &p) : ptr_(p) {
    }

    iterator(const iterator &it)
            : ptr_(const_cast<node_pointer>(it.node())) {
    }

    iterator(const iterator<container_type, iterator_tag, !is_const> &it)
            : ptr_(const_cast<node_pointer>(it.node())) {
    }

    iterator &operator=(const node_pointer &p) {
        ptr_ = p;
        return *this;
    }

    iterator &operator=(const iterator &p) {
        ptr_ = const_cast<node_pointer>(p.node());
        return *this;
    }

    iterator &operator=(const iterator<container_type, iterator_tag, !is_const> &p) {
        ptr_ = const_cast<node_pointer>(p.node());
        return *this;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, forward_iterator_tag>::value ||
        is_same<U, bidirectional_iterator_tag>::value ||
        is_same<U, random_access_iterator_tag>::value,
        iterator
    >::type &operator++() {
        detail::increment<node_pointer, value_pointer>(ptr_);
        return *this;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, forward_iterator_tag>::value ||
        is_same<U, bidirectional_iterator_tag>::value ||
        is_same<U, random_access_iterator_tag>::value,
        iterator
    >::type operator++(int) {
        auto tmp = *this;
        detail::increment<node_pointer, value_pointer>(ptr_);
        return tmp;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, bidirectional_iterator_tag>::value ||
        is_same<U, random_access_iterator_tag>::value,
        iterator
    >::type &operator--() {
        detail::decrement<node_pointer, value_pointer>(ptr_);
        return *this;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, bidirectional_iterator_tag>::value ||
        is_same<U, random_access_iterator_tag>::value,
        iterator
    >::type operator--(int) {
        auto tmp = *this;
        detail::decrement<node_pointer, value_pointer>(ptr_);
        return tmp;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, random_access_iterator_tag>::value, iterator
    >::type operator+(int i) const {
        return ptr_ + i;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, random_access_iterator_tag>::value, iterator
    >::type operator-(int i) const {
        return ptr_ - i;
    }

    template <typename U = iterator_tag>
    typename enable_if<
        is_same<U, random_access_iterator_tag>::value, size_t
    >::type operator-(const iterator &rhs) const {
        return ptr_ - rhs.ptr_;
    }

    value_reference operator*() {
        return *detail::entry<node_pointer, value_pointer>(ptr_);
    }

    value_pointer operator->() {
        return detail::entry<node_pointer, value_pointer>(ptr_);
    }

    bool operator==(const node_pointer &p) const {
        return ptr_ == const_cast<const node_type *>(p);
    }

    bool operator==(const iterator &i) const {
        return ptr_ == const_cast<const node_type *>(i.node());
    }

    bool operator==(const iterator<container_type, iterator_tag, !is_const> &i) const {
        return ptr_ == const_cast<node_type *>(i.node());
    }

    bool operator!=(const node_pointer &p) const {
        return ptr_ != const_cast<const node_type *>(p);
    }

    bool operator!=(const iterator &i) const {
        return ptr_ != const_cast<const node_type *>(i.node());
    }

    bool operator!=(const iterator<container_type, iterator_tag, !is_const> &i) const {
        return ptr_ != const_cast<node_type *>(i.node());
    }

    friend struct iterator<container_type, iterator_tag, !is_const>;

};

} // namespace detail

} // namespace yacppl

