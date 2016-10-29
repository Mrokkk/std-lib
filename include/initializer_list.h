#pragma once

namespace std {

template <typename Type>
class initializer_list {

    const Type *_array;
    unsigned int _size;

    initializer_list(const Type *array, unsigned int length)
        : _array(array), _size(length)
    { }

public:

    initializer_list()
        : _array(0), _size(0)
    { }

    unsigned int size() const {
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

