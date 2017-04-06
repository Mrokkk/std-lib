#pragma once

#include <cstddef>
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

        iterator &operator+(int i) {
            _ptr += i;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++_ptr;
            return tmp;
        }

        iterator &operator--() {
            --_ptr;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            --_ptr;
            return tmp;
        }

        Type &operator*() {
            return *_ptr;
        }

        Type *operator->() {
            return _ptr;
        }

        Type *get() const {
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

    class const_iterator {

        const Type *_ptr;

    public:

        explicit const_iterator(const Type *ptr)
            : _ptr(ptr) {}

        explicit const_iterator(const iterator &ptr)
            : _ptr(ptr.get()) {}

        const const_iterator &operator++() {
            ++_ptr;
            return *this;
        }

        const const_iterator &operator+(int i) {
            _ptr += i;
            return *this;
        }

        const_iterator operator++(int) {
            auto tmp = *this;
            ++_ptr;
            return tmp;
        }

        const const_iterator &operator--() {
            --_ptr;
            return *this;
        }

        const_iterator operator--(int) {
            auto tmp = *this;
            --_ptr;
            return tmp;
        }

        const Type &operator*() const {
            return *_ptr;
        }

        const Type *operator->() const {
            return _ptr;
        }

        size_t operator-(const const_iterator &rhs) const {
            return _ptr - rhs._ptr;
        }

        bool operator==(const const_iterator &element) const {
            return element._ptr == _ptr;
        }

        bool operator!=(const const_iterator &element) const {
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

    const_iterator cbegin() const {
        return const_iterator(_array);
    }

    iterator end() {
        return iterator(_array + _size);
    }

    const_iterator cend() const {
        return const_iterator(_array + _size);
    }

    Type *data() {
        return _array;
    }

    const Type *data() const {
        return _array;
    }

};

} // namespace yacppl

