#pragma once

#include "list.h"

namespace yacppl {

template<typename Type>
class stack final {

    list<Type> list_;

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

