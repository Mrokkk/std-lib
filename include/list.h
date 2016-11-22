#pragma once

namespace yacppl {

template<typename ElementType>
class list {

    struct list_element {

        ElementType data;
        list_element *prev = nullptr, *next = nullptr;

        list_element()
                : prev(this), next(this) {}

        list_element(const ElementType &e)
                : data(e), prev(this), next(this) {}

    };

    list_element _head;
    unsigned int _size = 0;

    list_element *backElement() const {
        return _head.prev;
    }

    list_element *frontElement() const {
        return _head.next;
    }

    void add(list_element *newElement, list_element *prev, list_element *next) {
        next->prev = newElement;
        prev->next = newElement;
        newElement->next = next;
        newElement->prev = prev;
        ++_size;
    }

    void del(list_element *prev, list_element *next) {
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --_size;
        delete temp;
    }

    void add_front_element(list_element *newElement) {
        add(newElement, &_head, _head.next);
    }

    void add_back_element(list_element *newElement) {
        add(newElement, _head.prev, &_head);
    }

    void delete_element(list_element *element) {
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

    void erase_elements(list_element *firstElement, const list_element *lastElement) {
        while (firstElement != lastElement) {
            auto temp = firstElement->prev;
            delete_element(firstElement);
            firstElement = temp->next;
        }
    }

public:

    class iterator {

    private:

        list_element *_node = nullptr;

    public:

        explicit iterator(list_element *node)
                : _node(node) {}

        list_element *node() const {
            return _node;
        }

        iterator &operator++() {
            _node = _node->next;
            return *this;
        }

        iterator operator++(int) {
            _node = _node->next;
            return *this;
        }

        iterator &operator--() {
            _node = _node->prev;
            return *this;
        }

        iterator operator--(int) {
            _node = _node->prev;
            return *this;
        }

        ElementType &operator*() const {
            return _node->data;
        }

        ElementType *operator->() const {
            return &_node->data;
        }

        bool operator!=(const iterator &element) const {
            return element._node != _node;
        }

        bool operator==(const iterator &element) const {
            return element._node == _node;
        }

    };

    list() = default;

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
        add_front_element(new list_element(element));
    }

    void push_back(const ElementType &element) {
        add_back_element(new list_element(element));
    }

    const ElementType &front() const {
        return frontElement()->data;
    }

    const ElementType &back() const {
        return backElement()->data;
    }

    iterator begin() const {
        return iterator(frontElement());
    }

    iterator end() const {
        return iterator(backElement()->next);
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

    void erase(iterator position) {
        erase_elements(position.node(), position.node()->next);
    }

    void erase(const iterator &first, const iterator &last) {
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

