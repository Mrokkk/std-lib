#pragma once

#include <list.h>

namespace yacppl {

template<typename ElementType>
class stack {

    list<ElementType> _list;

public:

    inline void push(const ElementType &element) {
        _list.push_back(element);
    }

    inline void pop() {
        _list.pop_back();
    }

    inline const ElementType &front() const {
        return _list.back();
    }

    inline unsigned long size() const {
        return _list.size();
    }

    inline stack &operator<<(const ElementType &element) {
        push(element);
        return *this;
    }

    inline stack &operator>>(ElementType &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

