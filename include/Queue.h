//
// Created by maciek on 15.06.16.
//

#pragma once

#include <List.h>

template <typename ElementType>
class Queue
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
        _list.pop_front();
    }

    constexpr inline const ElementType &front() const
    {
        return _list.front();
    }

    constexpr inline unsigned long size() const
    {
        return _list.size();
    }

    inline Queue &operator <<(const ElementType &element)
    {
        push(element);
        return *this;
    }

    inline Queue &operator >>(ElementType &element)
    {
        element = front();
        pop();
        return *this;
    }

};
