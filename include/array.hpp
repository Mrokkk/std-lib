#pragma once

#include <cstddef>
#include "iterator.hpp"
#include "initializer_list.hpp"

namespace yacppl {

template<typename Type, size_t Size = 0>
class array final
{
public:
    using value_type = Type;
    using node_type = Type;

private:
    template <bool is_const>
    using detail_iterator = detail::iterator<array, random_access_iterator_tag, is_const>;

public:
    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    array() = default;

    array(const std::initializer_list<Type>& container)
    {
        copy_elements_from(container);
    }

    template <typename Container>
    array(const Container& container)
    {
        copy_elements_from(container);
    }

    size_t size() const
    {
        return Size;
    }

    Type& operator[](const int index)
    {
        return array_[index];
    }

    iterator begin()
    {
        return iterator(array_);
    }

    const_iterator begin() const
    {
        return const_iterator(array_);
    }

    const_iterator end() const
    {
        return const_iterator(array_ + Size);
    }

    const_iterator cbegin() const
    {
        return const_iterator(array_);
    }

    iterator end() {
        return iterator(array_ + Size);
    }

    const_iterator cend() const
    {
        return const_iterator(array_ + Size);
    }

    Type *data()
    {
        return array_;
    }

private:
    template <typename Container>
    void copy_elements_from(const Container& container)
    {
        unsigned i = 0;
        for (auto it = container.begin(); it != container.end(); ++it)
        {
            array_[i++] = *it;
        }
    }

    Type array_[Size];
};

} // namespace yacppl
