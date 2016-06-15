//
// Created by maciek on 14.06.16.
//

#pragma once

#include <List.h>

template <typename ElementType>
class Stack
{
private:

    List<ElementType> _list;

public:

    inline void push(ElementType &element)
    {
        _list.push_back(element);
    }

    inline void push(const ElementType &element)
    {
        _list.push_back(element);
    }

    inline void pop()
    {
        _list.pop_back();
    }

    inline ElementType front()
    {
        return _list.back();
    }

    inline unsigned long size()
    {
        return _list.size();
    }

    inline Stack &operator <<(const ElementType &element)
    {
        push(element);
        return *this;
    }

    inline Stack &operator <<(ElementType &element)
    {
        push(element);
        return *this;
    }

    inline Stack &operator >>(ElementType &element)
    {
        element = front();
        pop();
        return *this;
    }

};
