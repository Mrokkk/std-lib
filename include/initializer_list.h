#pragma once

#include <stddef.h>

namespace std {

template <typename Type>
class initializer_list {

    const Type *array_;
    size_t size_;

public:

    initializer_list(const Type *array, size_t length) : array_(array), size_(length) {
    }

    size_t size() const {
        return size_;
    }

    const Type *begin() const {
        return array_;
    }

    const Type *end() const {
        return &array_[size_];
    }

    const Type *cbegin() const {
        return array_;
    }

    const Type *cend() const {
        return &array_[size_];
    }

};

} // namespace std

