#pragma once

#include <Exception.h>

template <typename ElementType>
struct ListElement {

    ElementType data;
    ListElement *prev = nullptr, *next = nullptr;

    inline ListElement()
        : prev(this), next(this)
    { }

    inline ListElement(const ElementType &e)
        : data(e), prev(this), next(this)
    { }

};

template <typename ElementType>
class ListIterator {

private:

    ListElement<ElementType> *_node = nullptr;

public:

    inline ListIterator() = delete;

    inline ListIterator(ListElement<ElementType> *node)
        : _node(node)
    { }

    inline ListElement<ElementType> *node() const {
        return _node;
    }

    inline ListIterator<ElementType> &operator ++() {
        _node = _node->next;
        return *this;
    }

    inline ListIterator<ElementType> operator ++(int dummy) {
        (void) dummy;
        _node = _node->next;
        return *this;
    }

    inline ListIterator<ElementType> &operator --() {
        _node = _node->prev;
        return *this;
    }

    inline ListIterator<ElementType> operator --(int dummy) {
        (void) dummy;
        _node = _node->prev;
        return *this;
    }

    inline ElementType &operator *() const {
        return _node->data;
    }

    inline ElementType *operator ->() const {
        return &_node->data;
    }

    inline bool operator !=(const ListIterator<ElementType> &element) const {
        return element._node != _node;
    }

    inline bool operator ==(const ListIterator<ElementType> &element) const {
        return element._node == _node;
    }

};

template <typename ElementType>
class List {

private:

    ListElement<ElementType> _head;
    unsigned int _size = 0;

    inline ListElement<ElementType> *backElement() const {
        return _head.prev;
    }

    inline ListElement<ElementType> *frontElement() const {
        return _head.next;
    }

    inline void add(ListElement<ElementType> *newElement, ListElement<ElementType> *prev,
                    ListElement<ElementType> *next) {
        next->prev = newElement;
        prev->next = newElement;
        newElement->next = next;
        newElement->prev = prev;
        ++_size;
    }

    inline void del(ListElement<ElementType> *prev, ListElement<ElementType> *next) {
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
        delete temp;
    }

    inline void addFrontElement(ListElement<ElementType> *newElement) {
        add(newElement, &_head, _head.next);
    }

    inline void addBackElement(ListElement<ElementType> *newElement) {
        add(newElement, _head.prev, &_head);
    }

    inline void deleteElement(ListElement<ElementType> *element) {
        del(element->prev, element->next);
    }

    template <typename Type>
    inline void copyElementsFrom(const Type &other) {
        for (const auto &e : other)
            push_back(e);
    }

    inline void moveElementsFrom(List<ElementType> &other) {
        while (other._size) {
            push_back(other.front());
            other.pop_front();
        }
    }

    inline void eraseElements(ListElement<ElementType> *firstElement, const ListElement<ElementType> *lastElement) {
        while (firstElement != lastElement) {
            auto temp = firstElement->prev;
            deleteElement(firstElement);
            firstElement = temp->next;
        }
    }

public:

    inline List()
    { }

    inline List(const std::initializer_list<ElementType> &list) {
        copyElementsFrom(list);
    }

    inline List(const List<ElementType> &list) {
        copyElementsFrom(list);
    }

    inline List(List<ElementType> &&list) {
        moveElementsFrom(list);
    }

    inline ~List() {
        clear();
    }

    inline unsigned int size() const {
        return _size;
    }

    inline void push_front(const ElementType &element) {
        addFrontElement(new ListElement<ElementType>(element));
    }

    inline void push_back(const ElementType &element) {
        addBackElement(new ListElement<ElementType>(element));
    }

    inline const ElementType &front() const {
        return frontElement()->data;
    }

    inline const ElementType &back() const {
        return backElement()->data;
    }

    inline ListIterator<ElementType> begin() const {
        return ListIterator<ElementType>(frontElement());
    }

    inline ListIterator<ElementType> end() const {
        return ListIterator<ElementType>(backElement()->next);
    }

    inline void pop_back() {
        eraseElements(backElement(), backElement()->next);
    }

    inline void pop_front() {
        eraseElements(frontElement(), frontElement()->next);
    }

    inline void clear() {
        eraseElements(frontElement(), backElement()->next);
    }

    inline void resize(unsigned long count, ElementType val = ElementType()) {
        if (_size < count) {
            while (_size != count)
                push_back(val);
        } else {
            while (_size != count)
                pop_back();
        }
    }

    inline void erase(ListIterator<ElementType> position) {
        eraseElements(position.node(), position.node()->next);
    }

    inline void erase(const ListIterator<ElementType> &first, const ListIterator<ElementType> &last) {
        eraseElements(first.node(), last.node());
    }

    inline List<ElementType> &operator =(const List<ElementType> &other) {
        clear();
        copyElementsFrom(other);
        return *this;
    }

    inline List<ElementType> &operator =(List<ElementType> &&other) {
        clear();
        moveElementsFrom(other);
        return *this;
    }

};

