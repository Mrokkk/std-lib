#pragma once

#include <cstddef>
#include "types.h"
#include "initializer_list.h"

namespace yacppl {

template<typename Type, size_t _size = 0>
class array {

    template <bool is_const>
    struct detail_iterator {

        using value_type = Type;
        using reference = typename conditional<is_const, const value_type &, value_type &>::type;
        using pointer = typename conditional<is_const, const value_type *, value_type *>::type;

    private:

        pointer _ptr = nullptr;

    public:

        detail_iterator(pointer ptr)
            : _ptr(ptr) {}

        detail_iterator(const detail_iterator<false> &it) : _ptr(it._ptr) {
        }

        detail_iterator(const detail_iterator<true> &it) : _ptr(it._ptr) {
        }

        detail_iterator &operator++() {
            ++_ptr;
            return *this;
        }

        detail_iterator operator+(int i) const {
            return _ptr + i;
        }

        detail_iterator operator++(int) {
            auto tmp = *this;
            ++_ptr;
            return tmp;
        }

        detail_iterator &operator--() {
            --_ptr;
            return *this;
        }

        detail_iterator operator--(int) {
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

        size_t operator-(const detail_iterator &rhs) const {
            return _ptr - rhs._ptr;
        }

        detail_iterator operator-(int i) const {
            return _ptr - i;
        }

        bool operator==(const detail_iterator &element) const {
            return element._ptr == _ptr;
        }

        bool operator!=(const detail_iterator &element) const {
            return element._ptr != _ptr;
        }

        friend struct detail_iterator<true>;

    };


    Type array_[_size];

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

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

