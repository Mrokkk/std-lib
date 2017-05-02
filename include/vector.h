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

    template <typename Container>
    void copy_from(const Container &container) {
        for (auto it = container.cbegin(); it != container.cend(); ++it) {
            push_back(*it);
        }
    }

    void release() {
        if (data_ != nullptr) {
            delete [] data_;
        }
    }

public:

    using node_type = Type;
    using value_type = Type;
    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    vector() = default;

    vector(const std::initializer_list<Type> &list) {
        copy_from(list);
    }

    template <typename Container>
    vector(Container &container) {
        copy_from(container);
    }

    vector(vector &&v) {
        data_ = v.data_;
        end_ = v.end_;
        max_size_ = v.max_size_;
        v.data_ = nullptr;
        v.end_ = nullptr;
        v.max_size_ = 0;
    }

    ~vector() {
        release();
    }

    vector &operator=(const vector &v) {
        clear();
        copy_from(v);
        return *this;
    }

    vector &operator=(vector &&v) {
        release();
        data_ = v.data_;
        end_ = v.end_;
        max_size_ = v.max_size_;
        v.data_ = nullptr;
        v.end_ = nullptr;
        v.max_size_ = 0;
        return *this;
    }

    vector &push_back(const Type &value) {
        if (data_ == nullptr) {
            allocate(2u);
        }
        else {
            if (size() + 1 > max_size_) {
                reallocate(max_size_ * 2);
            }
        }
        *end_++ = value;
        return *this;
    }

    vector &pop_back() {
        end_--;
        return *this;
    };

    const Type &front() const {
        return data_[0];
    }

    const Type &back() const {
        return end_[-1];
    }

    const Type &operator[](int index) const {
        return data_[index];
    }

    vector &clear() {
        end_ = data_;
        return *this;
    }

    iterator begin() {
        return iterator(data_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    const_iterator cbegin() const {
        return const_iterator(data_);
    }

    iterator end() {
        return iterator(end_);
    }

    const_iterator end() const {
        return const_iterator(end_);
    }

    const_iterator cend() const {
        return const_iterator(end_);
    }

    bool empty() const {
        return end_ - data_ == 0;
    }

    size_t size() const {
        return end_ - data_;
    }

};

} // namesace yacppl

