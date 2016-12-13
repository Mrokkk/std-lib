#pragma once

#include "list.h"

namespace yacppl {

template<typename Type>
class stack final {

    list<Type> _list;

public:

    void push(const Type &element) {
        _list.push_back(element);
    }

    void pop() {
        _list.pop_back();
    }

    const Type &front() const {
        return _list.back();
    }

    size_t size() const {
        return _list.size();
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

