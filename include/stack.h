#pragma once

#include "list.h"

namespace yacppl {

template<typename ElementType>
class stack final {

    list<ElementType> _list;

public:

    void push(const ElementType &element) {
        _list.push_back(element);
    }

    void pop() {
        _list.pop_back();
    }

    const ElementType &front() const {
        return _list.back();
    }

    size_t size() const {
        return _list.size();
    }

    stack &operator<<(const ElementType &element) {
        push(element);
        return *this;
    }

    stack &operator>>(ElementType &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

