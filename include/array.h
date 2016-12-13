#pragma once

#include <stddef.h>
#include "initializer_list.h"

namespace yacppl {

template<typename Type, size_t _size = 0>
class array {

    Type _array[_size];

public:

    class iterator {

        Type *_ptr;

    public:

        explicit iterator(Type *ptr)
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

        Type &operator*() {
            return *_ptr;
        }

        Type *operator->() {
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

    array() = default;

    array(std::initializer_list<Type> list) {
        unsigned i = 0;
        for (auto v : list)
            _array[i++] = v;
    }

    size_t size() const {
        return _size;
    }

    Type &operator[](int index) {
        return _array[index];
    }

    iterator begin() {
        return iterator(_array);
    }

    iterator end() {
        return iterator(_array + _size);
    }

    Type *data() {
        return _array;
    }

};

} // namespace yacppl

