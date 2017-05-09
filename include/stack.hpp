#pragma once

#include "list.hpp"

namespace yacppl {

template<typename Type, typename Container = list<Type>>
class stack final {

    Container list_;

public:

    void push(const Type &element) {
        list_.push_back(element);
    }

    void pop() {
        list_.pop_back();
    }

    const Type &front() const {
        return list_.back();
    }

    size_t size() const {
        return list_.size();
    }

    stack &operator<<(const Type &element) {
        push(element);
        return *this;
    }

    stack &operator>>(Type &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

