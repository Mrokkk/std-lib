#pragma once

#include <list.h>

namespace yacppl {

template<typename ElementType>
class queue {

    list<ElementType> _list;

public:

    void push(ElementType &element) {
        _list.push_back(element);
    }

    void push(const ElementType &element) {
        _list.push_back(element);
    }

    void pop() {
        _list.pop_front();
    }

    constexpr const ElementType &front() const {
        return _list.front();
    }

    constexpr unsigned long size() const {
        return _list.size();
    }

    queue &operator<<(const ElementType &element) {
        push(element);
        return *this;
    }

    queue &operator>>(ElementType &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

