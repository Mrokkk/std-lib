#pragma once

#include <stddef.h>
#include "initializer_list.h"

namespace yacppl {

template<typename ElementType, size_t _size = 0>
class array {

    ElementType _array[_size];

public:

    class iterator {

        ElementType *_ptr = nullptr;

    public:

        explicit iterator(ElementType *ptr)
            : _ptr(ptr) {}

        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator++(int) {
            ++_ptr;
            return *this;
        }

        iterator &operator--() {
            --_ptr;
            return *this;
        }

        iterator operator--(int) {
            --_ptr;
            return *this;
        }

        ElementType &operator*() {
            return *_ptr;
        }

        ElementType *operator->() {
            return _ptr;
        }

        size_t operator-(const iterator &rhs) const {
            return _ptr - rhs._ptr;
        }

        bool operator==(iterator &element) const {
            return element._ptr == _ptr;
        }

        bool operator!=(iterator &element) const {
            return element._ptr != _ptr;
        }

    };

    array() {}

    array(std::initializer_list<ElementType> list) {
        unsigned i = 0;
        for (auto v : list)
            _array[i++] = v;
    }

    auto size() const {
        return _size;
    }

    ElementType &operator[](int index) {
        return _array[index];
    }

    auto begin() {
        return iterator(_array);
    }

    auto end() {
        return iterator(_array + _size);
    }

    auto data() {
        return _array;
    }

};

} // namespace yacppl

