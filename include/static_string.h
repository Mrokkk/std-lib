#pragma once

#include "array.h"
#include "range.h"
#include "string.h"

namespace yacppl {

template <size_t _size>
class static_string final : public array<char, _size + 1> {

    using Array = array<char, _size + 1>;
    typename Array::iterator _ptr;

public:

    constexpr explicit static_string()
            : _ptr(Array::begin()) {
        for (size_t i = 0; i <= _size; i++) {
            Array::operator[](i) = 0;
        }
    }

    constexpr explicit static_string(const char *str)
            : _ptr(Array::begin()) {
        *this = str;
    }

    static_string &operator=(const char *str) {
        for (auto it : make_range(str)) {
            *_ptr = it;
            ++_ptr;
        }
        return *this;
    }

    auto begin() {
        return Array::begin();
    }

    auto cbegin() const {
        return Array::cbegin();
    }

    auto end() {
        return _ptr;
    }

    auto cend() const {
        return typename Array::const_iterator(_ptr);
    }

    size_t length() const {
        return typename Array::const_iterator(_ptr) - cbegin();
    }

    size_t size() const {
        return _size;
    }

    char operator[](int index) {
        return Array::operator[](index);
    }

    const char *get() const {
        return Array::data();
    }

    bool operator==(const char *str) const {
        return !compare(str, get());
    }

    bool operator!=(const char *str) const {
        return compare(str, get());
    }

};

} // namespace yacppl

