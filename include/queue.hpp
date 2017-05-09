#pragma once

#include "list.hpp"

namespace yacppl {

template<typename Type, typename Container = list<Type>>
class queue final {

    Container list_;

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

    const Type &front() const {
        return list_.front();
    }

    size_t size() const {
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

