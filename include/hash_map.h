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
struct hash_map final {

    using node = pair<Key, Value>;

    class iterator {

        list<node> **bucket_ptr_ = nullptr;
        list<node> **buckets_end_ = nullptr;
        unsigned bucket_index_ = 0;
        typename list<node>::iterator bucket_iterator_;
        typename list<node>::iterator end_;

        void advance() {
            if (bucket_index_ == Size) {
                return;
            }
            ++bucket_iterator_;
            if (bucket_iterator_ == end_) {
                bucket_index_++;
                while (bucket_ptr_[bucket_index_] == nullptr && bucket_index_ <= Size) {
                    bucket_index_++;
                }
                if (bucket_index_ == Size) {
                    bucket_iterator_ = nullptr;
                    return;
                }
                bucket_iterator_ = bucket_ptr_[bucket_index_]->begin();
                end_ = bucket_ptr_[bucket_index_]->end();
            }
        }

    public:

        iterator() = default;

        iterator(list<node> **ptr, unsigned bucket_index) : bucket_ptr_(ptr), bucket_index_(bucket_index) {
            bucket_iterator_ = bucket_ptr_[bucket_index_]->begin();
            end_ = bucket_ptr_[bucket_index_]->end();
        }

        iterator(unsigned bucket_index) : bucket_index_(bucket_index) {
        }

        iterator &operator++() {
            advance();
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            advance();
            return old;
        }

        node &operator*() {
            return *bucket_iterator_;
        }

        node *operator->() {
            return &*bucket_iterator_;
        }

        bool operator==(const iterator &it) const {
            return bucket_index_ == it.bucket_index_ && bucket_iterator_ == it.bucket_iterator_;
        }

        bool operator!=(const iterator &it) const {
            return not operator==(it);
        }

    };

private:

    list<node> *buckets_[Size];
    size_t size_ = 0u;

    void add_to_bucket(unsigned hash, const node &kv) {
        if (buckets_[hash] == nullptr) {
            buckets_[hash] = new list<node>;
        }
        buckets_[hash]->push_back(kv);
    }

    typename list<node>::iterator find_in_bucket(unsigned hash, const Key &key) const {
        if (buckets_[hash] == nullptr) {
            return nullptr;
        }
        for (auto it =  buckets_[hash]->begin(); it != buckets_[hash]->end(); ++it) {
            if (it->first == key) {
                return it;
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
        clear();
    }

    iterator begin() {
        return iterator(buckets_, 0);
    }

    iterator end() {
        return iterator(Size);
    }

    hash_map &insert(const node &kv) {
        auto index = get_bucket_index(kv.first);
        add_to_bucket(index, kv);
        ++size_;
        return *this;
    }

    hash_map &erase(const Key &key) {
        auto index = get_bucket_index(key);
        auto it = find_in_bucket(index, key);
        if (it == nullptr) {
            return *this;
        }
        buckets_[index]->erase(it);
        --size_;
        return *this;
    }

    hash_map &clear() {
        for (auto i = 0u; i < Size; ++i) {
            if (buckets_[i] != nullptr) {
                delete buckets_[i];
                buckets_[i] = nullptr;
            }
        }
        size_ = 0u;
        return *this;
    }

    const node *operator[](const Key &key) const {
        auto index = get_bucket_index(key);
        auto it = find_in_bucket(index, key);
        if (it == nullptr) {
            return nullptr;
        }
        return &(*it);
    }

    size_t size() const {
        return size_;
    }

    size_t max_bucket_count() const {
        return Size;
    }

    size_t bucket_count() const {
        size_t count = 0u;
        for (auto i = 0u; i < Size; ++i) {
            if (buckets_[i] != nullptr) {
                ++count;
            }
        }
        return count;
    }

};

} // namespace yacppl

