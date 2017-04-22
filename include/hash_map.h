#pragma once

#include <cstddef>
#include "pair.h"
#include "list.h"

namespace yacppl {

template <typename Key, typename Value, size_t Size = 32>
class hash_map {

public:

    using node = pair<Key, Value>;

private:

    list<node> *buckets_[Size];
    size_t size_ = 0u;

    // TODO: specialize for different types
    static unsigned hash_fn(const Key &k) {
        return k % Size;
    }

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
        auto hash = hash_fn(kv.first);
        add_to_bucket(hash, kv);
        return *this;
    }

    const node *operator[](const Key &key) const {
        auto hash = hash_fn(key);
        return find_in_bucket(hash, key);
    }

    size_t size() const {
        return 0u;
    }

};

} // namespace yacppl

