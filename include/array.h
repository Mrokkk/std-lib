#pragma once

#include <cstddef>
#include "initializer_list.h"

namespace yacppl {

template<typename Type, size_t _size = 0>
class array {

    Type array_[_size];

public:

    class iterator {

        Type *_ptr = nullptr;

    public:

        explicit iterator(Type *ptr)
            : _ptr(ptr) {}

        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator+(int i) const {
            return iterator(_ptr + i);
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

        iterator operator-(int i) const {
            return iterator(_ptr - i);
        }

        bool operator==(const iterator &element) const {
            return element._ptr == _ptr;
        }

        bool operator!=(const iterator &element) const {
            return element._ptr != _ptr;
        }

    };

    class const_iterator {

        const Type *_ptr = nullptr;

    public:

        explicit const_iterator(const Type *ptr)
            : _ptr(ptr) {}

        explicit const_iterator(const iterator &ptr)
            : _ptr(ptr.get()) {}

        const const_iterator &operator++() {
            ++_ptr;
            return *this;
        }

        const_iterator operator+(int i) const {
            return const_iterator(_ptr + i);
        }

        const_iterator operator++(int) const {
            auto tmp = const_iterator(_ptr);
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

        const_iterator operator-(int i) const {
            return const_iterator(_ptr - i);
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
            array_[i++] = v;
    }

    size_t size() const {
        return _size;
    }

    Type &operator[](int index) {
        return array_[index];
    }

    iterator begin() {
        return iterator(array_);
    }

    const_iterator cbegin() const {
        return const_iterator(array_);
    }

    iterator end() {
        return iterator(array_ + _size);
    }

    const_iterator cend() const {
        return const_iterator(array_ + _size);
    }

    Type *data() {
        return array_;
    }

    const Type *data() const {
        return array_;
    }

};

} // namespace yacppl

