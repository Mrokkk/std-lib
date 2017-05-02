#pragma once

#include "iterator.h"
#include "algorithm.h"
#include "initializer_list.h"

namespace yacppl {

template <typename Type>
class vector {

    template <bool is_const>
    using detail_iterator = detail::iterator<vector, random_access_iterator_tag, is_const>;

    Type *data_ = nullptr;
    Type *end_ = nullptr;
    size_t max_size_ = 0u;

    void allocate(size_t size) {
        data_ = new Type[size];
        max_size_ = size;
        end_ = data_;
    }

    void reallocate(size_t size) {
        auto old_size = this->size();
        auto new_data = new Type[size];
        copy(data_, new_data, old_size);
        delete [] data_;
        data_ = new_data;
        end_ = data_ + old_size;
        max_size_ = size;
    }

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

    ~vector() {
        if (data_) {
            delete [] data_;
        }
    }

    vector &push_back(const Type &value) {
        if (data_ == nullptr) {
            allocate(2u); // FIXME: why 2?
        }
        else {
            if (size() + 1 > max_size_) {
                reallocate(max_size_ * 2);
            }
        }
        *end_++ = value;
        return *this;
    }

    const Type &operator[](int index) {
        return data_[index];
    }

    iterator begin() {
        return iterator(data_);
    }

    iterator end() {
        return iterator(end_);
    }

    bool empty() const {
        return end_ - data_ == 0;
    }

    size_t size() const {
        return end_ - data_;
    }

};

} // namesace yacppl

