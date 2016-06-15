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

    inline ListElement<ElementType> *node()
    {
        return _node;
    }

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

    inline ListElement<ElementType> *last() const
    {
        return _head.prev;
    }

    inline ListElement<ElementType> *first() const
    {
        return _head.next;
    }

    inline void __add(ListElement<ElementType> *newElement, ListElement<ElementType> *prev,
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

    inline void addFrontElement(ListElement<ElementType> *newElement)
    {
        __add(newElement, &_head, _head.next);
    }

    inline void addBackElement(ListElement<ElementType> *newElement)
    {
        __add(newElement, _head.prev, &_head);
    }

    inline void deleteElement(ListElement<ElementType> *element)
    {
        __del(element->prev, element->next);
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
        while (list._size)
        {
            push_back(list.front());
            list.pop_front();
        }
    }

    inline ~List()
    {
        clear();
    }

    inline unsigned int size() const
    {
        return _size;
    }

    inline void push_front(ElementType element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        addFrontElement(newElement);
    }

    inline void push_back(ElementType element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        addBackElement(newElement);
    }

    inline ElementType front() const
    {
        if (!_size)
            throw EmptyContainerException();
        return first()->data;
    }

    inline ElementType back() const
    {
        if (!_size)
            throw EmptyContainerException();
        return last()->data;
    }

    inline ListIterator<ElementType> begin()
    {
        ListIterator<ElementType> it(first());
        return it;
    }

    inline ListIterator<ElementType> end()
    {
        ListIterator<ElementType> it(last()->next);
        return it;
    }

    inline void pop_back()
    {
        deleteElement(last());
    }

    inline void pop_front()
    {
        deleteElement(first());
    }

    inline void clear()
    {
        while (_size)
            pop_front();
    }

    inline void resize(unsigned long count, ElementType val = ElementType())
    {
        while (_size != count)
        {
            if (_size < count)
                push_back(val);
            else
                pop_back();
        }
    }

    inline void erase(ListIterator<ElementType> position)
    {
        deleteElement(position.node());
    }

    inline void erase(ListIterator<ElementType> first, ListIterator<ElementType> last)
    {
        auto firstElement = first.node();
        auto lastElement = last.node();
        while (firstElement != lastElement)
        {
            auto temp = firstElement->prev;
            deleteElement(firstElement);
            firstElement = temp->next;
        }
    }

    inline List<ElementType> &operator =(List<ElementType> &other)
    {
        clear();
        for (const auto &e : other)
            push_back(e);
    }

    inline List<ElementType> &operator =(List<ElementType> &&other)
    {
        clear();
        while (other._size)
        {
            push_back(other.front());
            other.pop_front();
        }
    }

};

