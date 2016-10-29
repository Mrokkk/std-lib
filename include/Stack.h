#pragma once

#include <List.h>

template <typename ElementType>
class Stack {

    List<ElementType> _list;

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

    inline Stack &operator <<(const ElementType &element) {
        push(element);
        return *this;
    }

    inline Stack &operator >>(ElementType &element) {
        element = front();
        pop();
        return *this;
    }

};

