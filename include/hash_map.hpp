#pragma once

#include <cstddef>
#include "pair.hpp"
#include "hash.hpp"
#include "list.hpp"
#include "types.hpp"

namespace yacppl {

template <
    typename Key,
    typename Value,
    size_t Size = 32,
    typename HashFn = ::yacppl::hash<Key>
>
struct hash_map final {

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

    template <bool is_const>
    class detail_iterator {

        using list_ptr = typename conditional<is_const, const list<node> *, list<node> *>::type;
        using list_iterator = typename conditional<is_const, typename list<node>::const_iterator,
              typename list<node>::iterator>::type;
        using list_array_ptr = typename conditional<is_const, const list_ptr *, list_ptr *>::type;
        using reference = typename conditional<is_const, const node &, node &>::type;
        using pointer = typename conditional<is_const, const node *, node *>::type;

        list_array_ptr bucket_ptr_ = nullptr;
        list_array_ptr buckets_end_ = nullptr;
        unsigned bucket_index_ = 0;
        list_iterator bucket_iterator_;
        list_iterator end_;

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

        detail_iterator(list_array_ptr ptr, unsigned bucket_index) : bucket_ptr_(ptr), bucket_index_(bucket_index) {
            bucket_iterator_ = bucket_ptr_[bucket_index_]->begin();
            end_ = bucket_ptr_[bucket_index_]->end();
        }

        detail_iterator(unsigned bucket_index) : bucket_index_(bucket_index) {
        }

    public:

        detail_iterator() = default;

        detail_iterator &operator++() {
            advance();
            return *this;
        }

        detail_iterator operator++(int) {
            detail_iterator old = *this;
            advance();
            return old;
        }

        reference operator*() {
            return *bucket_iterator_;
        }

        pointer operator->() {
            return &*bucket_iterator_;
        }

        bool operator==(const detail_iterator &it) const {
            return bucket_index_ == it.bucket_index_ && bucket_iterator_ == it.bucket_iterator_;
        }

        bool operator!=(const detail_iterator &it) const {
            return not operator==(it);
        }

        friend hash_map;
        friend detail_iterator<true>;
        friend detail_iterator<false>;

    };

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

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

    const_iterator begin() const {
        return const_iterator(buckets_, 0);
    }

    const_iterator cbegin() const {
        return const_iterator(buckets_, 0);
    }

    iterator end() {
        return iterator(Size);
    }

    const_iterator end() const {
        return const_iterator(Size);
    }

    const_iterator cend() const {
        return const_iterator(Size);
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

