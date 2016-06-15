//
// Created by maciek on 15.06.16.
//

#pragma once

#include <List.h>

template <typename ElementType>
class Queue : private List<ElementType>
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
        List<ElementType>::pop_front();
    }

    ElementType front()
    {
        return List<ElementType>::front();
    }

    unsigned long size()
    {
        return List<ElementType>::size();
    }

};
