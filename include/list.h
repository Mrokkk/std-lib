#pragma once

namespace yacppl {

template<typename ElementType>
struct list_element {

    ElementType data;
    list_element *prev = nullptr, *next = nullptr;

    inline list_element()
            : prev(this), next(this) {}

    inline list_element(const ElementType &e)
            : data(e), prev(this), next(this) {}

};

template<typename ElementType>
class list_iterator {

private:

    list_element<ElementType> *_node = nullptr;

public:

    explicit inline list_iterator(list_element<ElementType> *node)
            : _node(node) {}

    inline list_element<ElementType> *node() const {
        return _node;
    }

    inline list_iterator<ElementType> &operator++() {
        _node = _node->next;
        return *this;
    }

    inline list_iterator<ElementType> operator++(int dummy) {
        (void) dummy;
        _node = _node->next;
        return *this;
    }

    inline list_iterator<ElementType> &operator--() {
        _node = _node->prev;
        return *this;
    }

    inline list_iterator<ElementType> operator--(int) {
        _node = _node->prev;
        return *this;
    }

    inline ElementType &operator*() const {
        return _node->data;
    }

    inline ElementType *operator->() const {
        return &_node->data;
    }

    inline bool operator!=(const list_iterator<ElementType> &element) const {
        return element._node != _node;
    }

    inline bool operator==(const list_iterator<ElementType> &element) const {
        return element._node == _node;
    }

};

template<typename ElementType>
class list {

    list_element<ElementType> _head;
    unsigned int _size = 0;

    inline list_element<ElementType> *backElement() const {
        return _head.prev;
    }

    inline list_element<ElementType> *frontElement() const {
        return _head.next;
    }

    inline void add(list_element<ElementType> *newElement, list_element<ElementType> *prev,
                    list_element<ElementType> *next) {
        next->prev = newElement;
        prev->next = newElement;
        newElement->next = next;
        newElement->prev = prev;
        ++_size;
    }

    inline void del(list_element<ElementType> *prev, list_element<ElementType> *next) {
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
        delete temp;
    }

    inline void add_front_element(list_element<ElementType> *newElement) {
        add(newElement, &_head, _head.next);
    }

    inline void add_back_element(list_element<ElementType> *newElement) {
        add(newElement, _head.prev, &_head);
    }

    inline void delete_element(list_element<ElementType> *element) {
        del(element->prev, element->next);
    }

    template<typename Type>
    inline void copy_elements_from(const Type &other) {
        for (const auto &e : other)
            push_back(e);
    }

    inline void move_elements_from(list<ElementType> &other) {
        while (other._size) {
            push_back(other.front());
            other.pop_front();
        }
    }

    inline void erase_elements(list_element<ElementType> *firstElement, const list_element<ElementType> *lastElement) {
        while (firstElement != lastElement) {
            auto temp = firstElement->prev;
            delete_element(firstElement);
            firstElement = temp->next;
        }
    }

public:

    inline list() {}

    inline list(const std::initializer_list<ElementType> &list) {
        copy_elements_from(list);
    }

    inline list(const list<ElementType> &list) {
        copy_elements_from(list);
    }

    inline list(list<ElementType> &&list) {
        move_elements_from(list);
    }

    inline ~list() {
        clear();
    }

    inline unsigned int size() const {
        return _size;
    }

    inline void push_front(const ElementType &element) {
        add_front_element(new list_element<ElementType>(element));
    }

    inline void push_back(const ElementType &element) {
        add_back_element(new list_element<ElementType>(element));
    }

    inline const ElementType &front() const {
        return frontElement()->data;
    }

    inline const ElementType &back() const {
        return backElement()->data;
    }

    inline list_iterator<ElementType> begin() const {
        return list_iterator<ElementType>(frontElement());
    }

    inline list_iterator<ElementType> end() const {
        return list_iterator<ElementType>(backElement()->next);
    }

    inline void pop_back() {
        erase_elements(backElement(), backElement()->next);
    }

    inline void pop_front() {
        erase_elements(frontElement(), frontElement()->next);
    }

    inline void clear() {
        erase_elements(frontElement(), backElement()->next);
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

    inline void erase(list_iterator<ElementType> position) {
        erase_elements(position.node(), position.node()->next);
    }

    inline void erase(const list_iterator<ElementType> &first, const list_iterator<ElementType> &last) {
        erase_elements(first.node(), last.node());
    }

    inline list<ElementType> &operator=(const list<ElementType> &other) {
        clear();
        copy_elements_from(other);
        return *this;
    }

    inline list<ElementType> &operator=(list<ElementType> &&other) {
        clear();
        move_elements_from(other);
        return *this;
    }

};

} // namespace yacppl

