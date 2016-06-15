//
// Created by maciek on 14.06.16.
//

#pragma once

#include <List.h>

template <typename ElementType>
class Stack : private List<ElementType>
{
public:

    inline void push(ElementType &element)
    {
        List<ElementType>::push_back(element);
    }

    inline void push(const ElementType &element)
    {
        List<ElementType>::push_back(element);
    }

    inline void pop()
    {
        List<ElementType>::pop_back();
    }

    inline ElementType front()
    {
        return List<ElementType>::back();
    }

    inline unsigned long size()
    {
        return List<ElementType>::size();
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
