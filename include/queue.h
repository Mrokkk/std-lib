#pragma once

#include "list.h"

namespace yacppl {

template<typename Type>
class queue final {

    list<Type> list_;

public:

    void push(Type &element) {
        list_.push_back(element);
    }

    void push(const Type &element) {
        list_.push_back(element);
    }

    void pop() {
        list_.pop_front();
    }

    constexpr const Type &front() const {
        return list_.front();
    }

    constexpr size_t size() const {
        return list_.size();
    }

    queue &operator<<(const Type &element) {
        push(element);
        return *this;
    }

    queue &operator>>(Type &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

