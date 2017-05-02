#pragma once

#include "iterator.h"
#include "initializer_list.h"

namespace yacppl {

template <typename Type>
class vector {

    template <bool is_const>
    using detail_iterator = detail::iterator<vector, random_access_iterator_tag, is_const>;

    Type *data_ = nullptr;

public:

    using node_type = Type;
    using value_type = Type;
    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    vector() = default;

    iterator begin() {
        return iterator();
    }

    iterator end() {
        return iterator();
    }

    bool empty() const {
        return true;
    }

    size_t size() const {
        return 0;
    }

};

} // namesace yacppl

