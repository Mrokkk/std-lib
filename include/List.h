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

    inline ListElement<ElementType> *backElement() const
    {
        return _head.prev;
    }

    inline ListElement<ElementType> *frontElement() const
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
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
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

    inline void copyElementsFrom(List<ElementType> &other)
    {
        for (const auto &e : other)
            push_back(e);
    }

    inline void moveElementsFrom(List<ElementType> &other)
    {
        while (other._size)
        {
            push_back(other.front());
            other.pop_front();
        }
    }

    inline void eraseElements(ListElement<ElementType> *firstElement, const ListElement<ElementType> *lastElement)
    {
        while (firstElement != lastElement)
        {
            auto temp = firstElement->prev;
            deleteElement(firstElement);
            firstElement = temp->next;
        }
    }

public:

    explicit inline List()
    { }

    explicit inline List(List<ElementType> &list)
    {
        copyElementsFrom(list);
    }

    explicit inline List(List<ElementType> &&list)
    {
        moveElementsFrom(list);
    }

    inline ~List()
    {
        clear();
    }

    inline unsigned int size() const
    {
        return _size;
    }

    inline void push_front(const ElementType &element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        addFrontElement(newElement);
    }

    inline void push_back(const ElementType &element)
    {
        ListElement<ElementType> *newElement = new ListElement<ElementType>(element);
        addBackElement(newElement);
    }

    inline const ElementType &front() const
    {
        if (!_size)
            throw EmptyContainerException();
        return frontElement()->data;
    }

    inline const ElementType &back() const
    {
        if (!_size)
            throw EmptyContainerException();
        return backElement()->data;
    }

    inline ListIterator<ElementType> begin()
    {
        ListIterator<ElementType> it(frontElement());
        return it;
    }

    inline ListIterator<ElementType> end()
    {
        ListIterator<ElementType> it(backElement()->next);
        return it;
    }

    inline void pop_back()
    {
        deleteElement(backElement());
    }

    inline void pop_front()
    {
        deleteElement(frontElement());
    }

    inline void clear()
    {
        eraseElements(frontElement(), backElement()->next);
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
        eraseElements(first.node(), last.node());
    }

    inline List<ElementType> &operator =(List<ElementType> &other)
    {
        clear();
        copyElementsFrom(other);
    }

    inline List<ElementType> &operator =(List<ElementType> &&other)
    {
        clear();
        moveElementsFrom(other);
    }

};

