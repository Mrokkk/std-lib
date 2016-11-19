#pragma once

namespace yacppl {

template<typename ElementType>
struct list_element {

    ElementType data;
    list_element *prev = nullptr, *next = nullptr;

    list_element()
            : prev(this), next(this) {}

    list_element(const ElementType &e)
            : data(e), prev(this), next(this) {}

};

template<typename ElementType>
class list_iterator {

private:

    list_element<ElementType> *_node = nullptr;

public:

    explicit list_iterator(list_element<ElementType> *node)
            : _node(node) {}

    list_element<ElementType> *node() const {
        return _node;
    }

    list_iterator<ElementType> &operator++() {
        _node = _node->next;
        return *this;
    }

    list_iterator<ElementType> operator++(int dummy) {
        (void) dummy;
        _node = _node->next;
        return *this;
    }

    list_iterator<ElementType> &operator--() {
        _node = _node->prev;
        return *this;
    }

    list_iterator<ElementType> operator--(int) {
        _node = _node->prev;
        return *this;
    }

    ElementType &operator*() const {
        return _node->data;
    }

    ElementType *operator->() const {
        return &_node->data;
    }

    bool operator!=(const list_iterator<ElementType> &element) const {
        return element._node != _node;
    }

    bool operator==(const list_iterator<ElementType> &element) const {
        return element._node == _node;
    }

};

template<typename ElementType>
class list {

    list_element<ElementType> _head;
    unsigned int _size = 0;

    list_element<ElementType> *backElement() const {
        return _head.prev;
    }

    list_element<ElementType> *frontElement() const {
        return _head.next;
    }

    void add(list_element<ElementType> *newElement, list_element<ElementType> *prev,
                    list_element<ElementType> *next) {
        next->prev = newElement;
        prev->next = newElement;
        newElement->next = next;
        newElement->prev = prev;
        ++_size;
    }

    void del(list_element<ElementType> *prev, list_element<ElementType> *next) {
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
        delete temp;
    }

    void add_front_element(list_element<ElementType> *newElement) {
        add(newElement, &_head, _head.next);
    }

    void add_back_element(list_element<ElementType> *newElement) {
        add(newElement, _head.prev, &_head);
    }

    void delete_element(list_element<ElementType> *element) {
        del(element->prev, element->next);
    }

    template<typename Type>
    void copy_elements_from(const Type &other) {
        for (const auto &e : other)
            push_back(e);
    }

    void move_elements_from(list<ElementType> &other) {
        while (other._size) {
            push_back(other.front());
            other.pop_front();
        }
    }

    void erase_elements(list_element<ElementType> *firstElement, const list_element<ElementType> *lastElement) {
        while (firstElement != lastElement) {
            auto temp = firstElement->prev;
            delete_element(firstElement);
            firstElement = temp->next;
        }
    }

public:

    list() {}

    list(const std::initializer_list<ElementType> &list) {
        copy_elements_from(list);
    }

    list(const list<ElementType> &list) {
        copy_elements_from(list);
    }

    list(list<ElementType> &&list) {
        move_elements_from(list);
    }

    ~list() {
        clear();
    }

    unsigned int size() const {
        return _size;
    }

    void push_front(const ElementType &element) {
        add_front_element(new list_element<ElementType>(element));
    }

    void push_back(const ElementType &element) {
        add_back_element(new list_element<ElementType>(element));
    }

    const ElementType &front() const {
        return frontElement()->data;
    }

    const ElementType &back() const {
        return backElement()->data;
    }

    list_iterator<ElementType> begin() const {
        return list_iterator<ElementType>(frontElement());
    }

    list_iterator<ElementType> end() const {
        return list_iterator<ElementType>(backElement()->next);
    }

    void pop_back() {
        erase_elements(backElement(), backElement()->next);
    }

    void pop_front() {
        erase_elements(frontElement(), frontElement()->next);
    }

    void clear() {
        erase_elements(frontElement(), backElement()->next);
    }

    void resize(unsigned long count, ElementType val = ElementType()) {
        if (_size < count) {
            while (_size != count)
                push_back(val);
        } else {
            while (_size != count)
                pop_back();
        }
    }

    void erase(list_iterator<ElementType> position) {
        erase_elements(position.node(), position.node()->next);
    }

    void erase(const list_iterator<ElementType> &first, const list_iterator<ElementType> &last) {
        erase_elements(first.node(), last.node());
    }

    list<ElementType> &operator=(const list<ElementType> &other) {
        clear();
        copy_elements_from(other);
        return *this;
    }

    list<ElementType> &operator=(list<ElementType> &&other) {
        clear();
        move_elements_from(other);
        return *this;
    }

};

} // namespace yacppl

