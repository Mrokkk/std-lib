#pragma once

#include <stddef.h>

namespace std {

template <typename Type>
class initializer_list {

    const Type *_array = nullptr;
    size_t _size = 0;

    initializer_list(const Type *array, size_t length)
        : _array(array), _size(length) {}

public:

    constexpr initializer_list() {}

    size_t size() const {
        return _size;
    }

    const Type *begin() const {
        return _array;
    }

    const Type *end() const {
        return &_array[_size];
    }

};

} // namespace std

