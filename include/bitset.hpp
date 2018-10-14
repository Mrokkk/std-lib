#pragma once

#include <cstddef>
#include <cstdint>

namespace yacppl
{

template <size_t Size>
struct bitset final
{
    using value_type = size_t;

    struct reference final
    {
        constexpr reference() = default;

        constexpr explicit reference(value_type* ptr, const size_t bit)
            : ptr_(ptr)
            , bit_(bit)
        {
        }

        operator bool() const
        {
            return *ptr_ & (1 << bit_);
        }

        reference& operator=(const bool v)
        {
            if (v)
            {
                *ptr_ |= (1 << bit_);
            }
            else
            {
                *ptr_ &= ~(1 << bit_);
            }
            return *this;
        }

    private:
        value_type* ptr_ = nullptr;
        size_t bit_ = 0u;
    };

    constexpr bitset()
        : data_{}
    {
    }

    bitset& set(const size_t index)
    {
        data_[index / value_type_bits()] |= (1 << index % value_type_bits());
        return *this;
    }

    bitset& reset(const size_t index)
    {
        data_[index / value_type_bits()] &= ~(1 << index % value_type_bits());
        return *this;
    }

    bitset& flip(const size_t index)
    {
        data_[index / value_type_bits()] ^= (1 << index % value_type_bits());
        return *this;
    }

    reference operator[](const size_t index)
    {
        return reference(&data_[index / value_type_bits()], index % value_type_bits());
    }

    constexpr bool operator[](const size_t index) const
    {
        return data_[index / value_type_bits()] & (1 << index % value_type_bits());
    }

    constexpr size_t size() const
    {
        return Size;
    }

private:
    constexpr static size_t value_type_bits()
    {
        return sizeof(value_type) * 8;
    }

    value_type data_[(Size + value_type_bits() - 1) / value_type_bits()];
};

} // namespace yacppl
