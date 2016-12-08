#pragma once

#include "array.h"

namespace yacppl {

template <size_t _size>
class static_string : public array<char, _size + 1> {

    using Array = array<char, _size + 1>;
    typename Array::iterator _ptr;

    int strcmp(const char *string1, const char *string2) {
        if (string1 == 0 || string2 == 0) return 1;
        while (1) {
            if (*string1++ != *string2++)
                return 1;
            if (*string1 == '\0' && *string2 == '\0')
                return 0;
            if (*string1 == '\0' || *string2 == '\0')
                return 1;
        }
        return 0;
    }

public:

    explicit static_string()
            : _ptr(Array::begin()) {
        for (size_t i = 0; i <= _size; i++) {
            Array::operator[](i) = 0;
        }
    }

    static_string &operator=(const char *str) {
        for (auto i = 0u; str[i] != 0; ++i) {
            Array::operator[](i) = str[i];
            ++_ptr;
        }
        return *this;
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

    const char *get() {
        return Array::data();
    }

    bool operator==(const char *str) {
        return !strcmp(str, Array::data());
    }

};

} // namespace yacppl

