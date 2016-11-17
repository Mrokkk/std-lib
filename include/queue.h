#pragma once

#include <list.h>

namespace yacppl {

template<typename ElementType>
class queue {

    list<ElementType> _list;

public:

    inline void push(ElementType &element) {
        _list.push_back(element);
    }

    inline void push(const ElementType &element) {
        _list.push_back(element);
    }

    inline void pop() {
        _list.pop_front();
    }

    constexpr inline const ElementType &front() const {
        return _list.front();
    }

    constexpr inline unsigned long size() const {
        return _list.size();
    }

    inline queue &operator<<(const ElementType &element) {
        push(element);
        return *this;
    }

    inline queue &operator>>(ElementType &element) {
        element = front();
        pop();
        return *this;
    }

};

} // namespace yacppl

