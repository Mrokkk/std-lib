#pragma once

#include <cstddef>
#include <cstdint>

namespace yacppl {

template <size_t Size>
class bitset {

    constexpr static size_t value_type_bits() {
        return sizeof(value_type) * 8;
    }

    using value_type = size_t;
    value_type data_[(Size + value_type_bits() - 1) / value_type_bits()];

public:

    class reference {

        value_type *ptr_ = nullptr;
        size_t bit_ = 0u;

    public:

        reference() = default;

        explicit reference(value_type *ptr, size_t bit) : ptr_(ptr), bit_(bit) {
        }

        operator bool() const {
            return *ptr_ & (1 << bit_);
        }

        reference &operator=(bool v) {
            if (v) {
                *ptr_ |= (1 << bit_);
            }
            else {
                *ptr_ &= ~(1 << bit_);
            }
            return *this;
        }

    };

    bitset() : data_{} {
    }

    bitset &set(size_t index) {
        data_[index / value_type_bits()] |= (1 << index % value_type_bits());
        return *this;
    }

    bitset &reset(size_t index) {
        data_[index / value_type_bits()] &= ~(1 << index % value_type_bits());
        return *this;
    }

    bitset &flip(size_t index) {
        data_[index / value_type_bits()] ^= (1 << index % value_type_bits());
        return *this;
    }

    reference operator[](size_t index) {
        return reference(&data_[index / value_type_bits()], index % value_type_bits());
    }

    constexpr bool operator[](size_t index) const {
        return data_[index / value_type_bits()] & (1 << index % value_type_bits());
    }

    size_t size() const {
        return Size;
    }

};

} // namespace yacppl

