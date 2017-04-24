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

inline auto begin(char *c) {
    return c;
}

inline auto cbegin(const char *c) {
    return c;
}

inline size_t length(const char *string) {
    const char *temp;
    for (temp = string; *temp != 0; ++temp);
    return temp-string;
}

inline auto end(char *c) {
    return begin(c) + length(c);
}

inline auto cend(const char *c) {
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

template <typename value_type, bool is_const>
struct pointer_iterator {

    using reference = typename conditional<is_const, const value_type &, value_type &>::type;
    using pointer = typename conditional<is_const, const value_type *, value_type *>::type;

private:

    pointer _ptr = nullptr;

public:

    pointer_iterator(pointer ptr)
        : _ptr(ptr) {}

    pointer_iterator(const pointer_iterator<value_type, false> &it) : _ptr(it._ptr) {
    }

    pointer_iterator(const pointer_iterator<value_type, true> &it) : _ptr(it._ptr) {
    }

    pointer_iterator &operator++() {
        ++_ptr;
        return *this;
    }

    pointer_iterator operator+(int i) const {
        return _ptr + i;
    }

    pointer_iterator operator++(int) {
        auto tmp = *this;
        ++_ptr;
        return tmp;
    }

    pointer_iterator &operator--() {
        --_ptr;
        return *this;
    }

    pointer_iterator operator--(int) {
        auto tmp = *this;
        --_ptr;
        return tmp;
    }

    reference operator*() {
        return *_ptr;
    }

    pointer operator->() {
        return _ptr;
    }

    pointer get() {
        return _ptr;
    }

    size_t operator-(const pointer_iterator &rhs) const {
        return _ptr - rhs._ptr;
    }

    pointer_iterator operator-(int i) const {
        return _ptr - i;
    }

    bool operator==(const pointer_iterator &element) const {
        return element._ptr == _ptr;
    }

    bool operator!=(const pointer_iterator &element) const {
        return element._ptr != _ptr;
    }

    friend struct pointer_iterator<value_type, true>;

};

template <typename value_type, typename node_type, bool is_const>
struct list_iterator {

    using node_pointer = typename conditional<is_const, const node_type *, node_type *>::type;
    using reference = typename conditional<is_const, const value_type &, value_type &>::type;
    using pointer = typename conditional<is_const, const value_type *, value_type *>::type;

private:

    node_pointer ptr = nullptr;

public:

    list_iterator() = default;

    list_iterator(node_pointer p) : ptr(p) {
    }

    list_iterator(const list_iterator<value_type, node_pointer, true> &it) : ptr(it.ptr) {
    }

    list_iterator(const list_iterator<value_type, node_pointer, false> &it) : ptr(it.ptr) {
    }

    list_iterator &operator++() {
        ptr = ptr->next();
        return *this;
    }

    list_iterator operator++(int) {
        auto tmp = *this;
        ptr = ptr->next();
        return tmp;
    }

    list_iterator &operator--() {
        ptr = ptr->prev();
        return *this;
    }

    list_iterator operator--(int) {
        auto tmp = *this;
        ptr = ptr->prev();
        return tmp;
    }

    reference operator *() {
        return *ptr->entry();
    }

    pointer operator->() {
        return ptr->entry();
    }

    bool operator==(const list_iterator &i) const {
        return i.ptr == ptr;
    }

    bool operator!=(const list_iterator &i) const {
        return i.ptr != ptr;
    }

    node_pointer node() {
        return ptr;
    }

    const node_pointer node() const {
        return ptr;
    }

    friend struct list_iterator<value_type, node_type, true>;

};


} // namespace yacppl

