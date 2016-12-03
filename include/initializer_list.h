#pragma once

#include <stddef.h>

namespace std {

template <typename Type>
class initializer_list {

    const Type *_array;
    size_t _size;

    initializer_list(const Type *array, size_t length)
        : _array(array), _size(length)
    { }

public:

    initializer_list()
        : _array(0), _size(0)
    { }

    auto size() const {
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

