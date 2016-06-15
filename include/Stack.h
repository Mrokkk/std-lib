//
// Created by maciek on 14.06.16.
//

#pragma once

#include <List.h>

template <typename ElementType>
class Stack : private List<ElementType>
{
public:

    void push(ElementType &element)
    {
        List<ElementType>::push_back(element);
    }

    void push(const ElementType &element)
    {
        List<ElementType>::push_back(element);
    }

    void pop()
    {
        List<ElementType>::pop_back();
    }

    ElementType front()
    {
        return List<ElementType>::back();
    }

    unsigned long size()
    {
        return List<ElementType>::size();
    }

};
