#pragma once

#include "array.h"

namespace yacppl {

template <size_t _size>
class static_string : public array<char, _size + 1> {

    using Array = array<char, _size + 1>;
    typename Array::iterator _ptr;

public:

    static_string()
            : _ptr(Array::begin()) {
        for (size_t i = 0; i <= _size; i++)
            Array::operator[](i) = 0;
    }

    auto begin() {
        return Array::begin();
    }

    auto end() {
        return _ptr;
    }

    auto length() {
        return _ptr - begin();
    }

    auto size() {
        return _size;
    }

    char operator[](int index) {
        return Array::operator[](index);
    }

};

} // namespace yacppl

