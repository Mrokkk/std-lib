#pragma once

template <typename Type>
class inherited_list {

    Type *_prev, *_next;

    void add_element(Type *new_element, Type *prev, Type *next) {
        next->_prev = new_element;
        prev->_next = new_element;
        new_element->_next = next;
        new_element->_prev = prev;
    }

public:

    class iterator {

        Type *_ptr = nullptr;

    public:

        iterator(Type *t)
            : _ptr(t) {}

        iterator &operator++() {
            _ptr = _ptr->next();
            return *this;
        }

        iterator operator++(int) {
            _ptr = _ptr->next();
            return *this;
        }

        iterator &operator--() {
            _ptr = _ptr->prev();
            return *this;
        }

        iterator operator--(int) {
            _ptr = _ptr->prev();
            return *this;
        }

        Type &operator*() {
            return *_ptr;
        }

        Type *operator->() {
            return _ptr;
        }

        bool operator!=(const iterator &comp) {
            return _ptr != comp._ptr;
        }

    };

    inherited_list() {
        _prev = reinterpret_cast<Type *>(this);
        _next = reinterpret_cast<Type *>(this);
    }

    Type &add(Type *new_element) {
        add_element(new_element, _prev, reinterpret_cast<Type *>(this));
        return *reinterpret_cast<Type *>(this);
    }

    Type &remove() {
        _next->prev = _prev;
        _prev->next = _next;
        _next = reinterpret_cast<Type *>(this);
        _prev = reinterpret_cast<Type *>(this);
        return *reinterpret_cast<Type *>(this);
    }

    Type *next() {
        return _next;
    }

    Type *prev() {
        return _prev;
    }

    bool empty() {
        return _next == reinterpret_cast<Type *>(this) && _next == reinterpret_cast<Type *>(this);
    }

    auto begin() {
        return iterator(_next);
    }

    auto end() {
        return iterator(reinterpret_cast<Type *>(this));
    }

};

