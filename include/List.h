//
// Created by maciek on 12.06.16.
//

#pragma once

#include <Exception.h>

template <typename ElementType>
struct ListElement
{

    ElementType data;
    ListElement *prev = nullptr, *next = nullptr;

    inline ListElement()
        : prev(this), next(this)
    { }

    inline ListElement(ElementType e)
        : data(e), prev(this), next(this)
    { }

};

template <typename ElementType>
class ListIterator
{
private:
    ListElement<ElementType> *_node = nullptr;

public:

    inline ListIterator() = delete;

    inline ListIterator(ListElement<ElementType> *node)
        : _node(node)
    { }

    inline ListIterator<ElementType> &operator ++()
    {
        _node = _node->next;
        return *this;
    }

    inline ListIterator<ElementType> operator ++(int dummy)
    {
        (void) dummy;
        _node = _node->next;
        return *this;
    }

    inline ListIterator<ElementType> &operator --()
    {
        _node = _node->prev;
        return *this;
    }

    inline ListIterator<ElementType> operator --(int dummy)
    {
        (void) dummy;
        _node = _node->prev;
        return *this;
    }

    inline ElementType &operator *()
    {
        return _node->data;
    }

    inline ElementType *operator ->()
    {
        return &_node->data;
    }

    inline bool operator !=(ListIterator<ElementType> &element) const
    {
        return element._node != _node;
    }

    inline bool operator ==(ListIterator<ElementType> &element) const
    {
        return element._node == _node;
    }

};

template <typename ElementType>
class List
{
private:

    ListElement<ElementType> _head;
    unsigned int _size = 0;

    inline void _add(ListElement<ElementType> *newElement, ListElement<ElementType> *prev,
                     ListElement<ElementType> *next)
    {
        next->prev = newElement;
        prev->next = newElement;
        newElement->next = next;
        newElement->prev = prev;
        ++_size;
    }

    inline void __del(ListElement<ElementType> *prev, ListElement<ElementType> *next)
    {
        if (!_size)
            throw EmptyContainerException();
        ListElement<ElementType> *temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
        if (temp)
            delete temp;
    }

public:

    explicit inline List()
    { }

    explicit inline List(List<ElementType> &list)
    {
        for (auto e : list)
            push_back(e);
    }

    explicit inline List(List<ElementType> &&list)
    {
        for (auto e : list)
            push_back(e);
        while (list._size)
            list.pop_front();
    }

    inline ~List()
    {
        while (_size)
            pop_front();
    }

    inline unsigned int size() const
    {
        return _size;
    }

    inline void push_front(ElementType element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        _add(newElement, &_head, _head.next);
    }

    inline void push_back(ElementType element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        _add(newElement, _head.prev, &_head);
    }

    inline ElementType front() const
    {
        if (!_size)
            throw EmptyContainerException();
        return _head.next->data;
    }

    inline ElementType back() const
    {
        if (!_size)
            throw EmptyContainerException();
        return _head.prev->data;
    }

    inline ListIterator<ElementType> begin()
    {
        ListIterator<ElementType> it(_head.next);
        return it;
    }

    inline ListIterator<ElementType> end()
    {
        ListIterator<ElementType> it(&_head);
        return it;
    }

    inline void pop_back()
    {
        __del(_head.prev->prev, _head.prev->next);
    }

    inline void pop_front()
    {
        __del(_head.next->prev, _head.next->next);
    }

    inline List<ElementType> &operator =(List<ElementType> &other)
    {
        while (_size)
            pop_front();
        for (const auto &e : other)
            push_back(e);
    }

    inline List<ElementType> &operator =(List<ElementType> &&other)
    {
        while (_size)
            pop_front();
        for (const auto &e : other)
            push_back(e);
        while (other._size)
            other.pop_front();
    }

};

