#pragma once

#include "iterator.h"
#include "initializer_list.h"

namespace yacppl {

template <typename Type>
class vector {

    template <bool is_const>
    using detail_iterator = detail::iterator<vector, random_access_iterator_tag, is_const>;

    Type *data_ = nullptr;
    size_t size_ = 0u;

public:

    using node_type = Type;
    using value_type = Type;
    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    vector() = default;

    vector(const std::initializer_list<Type> &list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            push_back(*it);
        }
    }

    vector &push_back(const Type &) {
        // TODO
        return *this;
    }

    iterator begin() {
        return iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    bool empty() const {
        return true;
    }

    size_t size() const {
        return 0;
    }

};

} // namesace yacppl

