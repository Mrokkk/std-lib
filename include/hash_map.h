#pragma once

#include <cstddef>
#include "pair.h"
#include "hash.h"
#include "list.h"

namespace yacppl {

template <
    typename Key,
    typename Value,
    size_t Size = 32,
    typename HashFn = ::yacppl::hash<Key>
>
class hash_map {

public:

    using node = pair<Key, Value>;

private:

    list<node> *buckets_[Size];
    size_t size_ = 0u;

    void add_to_bucket(unsigned hash, const node &kv) {
        if (buckets_[hash] == nullptr) {
            buckets_[hash] = new list<node>;
        }
        buckets_[hash]->push_back(kv);
    }

    const node *find_in_bucket(unsigned hash, const Key &key) const {
        if (buckets_[hash] == nullptr) {
            return nullptr;
        }
        for (const auto &node : *buckets_[hash]) {
            if (node.first == key) {
                return &node;
            }
        }
        return nullptr;
    }

    unsigned get_bucket_index(const Key &key) const {
        HashFn hash_fn;
        return hash_fn(key) % Size;
    }

public:

    hash_map() {
        for (auto i = 0u; i < Size; ++i) {
            buckets_[i] = nullptr;
        }
    }

    ~hash_map() {
        for (auto i = 0u; i < Size; ++i) {
            if (buckets_[i] != nullptr) {
                delete buckets_[i];
            }
        }
    }

    hash_map &append(const node &kv) {
        auto index = get_bucket_index(kv.first);
        add_to_bucket(index, kv);
        return *this;
    }

    const node *operator[](const Key &key) const {
        auto index = get_bucket_index(key);
        return find_in_bucket(index, key);
    }

    size_t size() const {
        return 0u;
    }

};

} // namespace yacppl

