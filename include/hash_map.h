#pragma once

#include <cstddef>
#include "list.h"

namespace yacppl {

template <typename Key, typename Value, size_t Size = 20>
class hash_map {

    struct node {
        Value value;
        Key key;
    };

    list<node> *buckets_[Size];
    size_t size_ = 0u;

public:

    hash_map() = default;

    hash_map &append(const Key &, const Value &) {
        return *this;
    }

    size_t size() const {
        return 0u;
    }

};

} // namespace yacppl

