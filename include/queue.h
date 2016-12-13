#pragma once

#include "list.h"

namespace yacppl {

template<typename Type>
class queue final {

    list<Type> _list;

public:

    void push(Type &element) {
        _list.push_back(element);
    }

    void push(const Type &element) {
        _list.push_back(element);
    }

    void pop() {
        _list.pop_front();
    }

    constexpr const Type &front() const {
        return _list.front();
    }

    constexpr unsigned long size() const {
        return _list.size();
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

