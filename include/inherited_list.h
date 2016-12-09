#pragma once

namespace yacppl {

template <typename Type>
class inherited_list {

    Type *_prev, *_next;

    void add_element(Type &new_element, Type &prev, Type &next) {
        next._prev = &new_element;
        prev._next = &new_element;
        new_element._next = &next;
        new_element._prev = &prev;
    }

    operator Type &() {
        return *reinterpret_cast<Type *>(this);
    }

public:

    class iterator {

        Type *_ptr = nullptr;

    public:

        constexpr iterator(Type *t)
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

    constexpr inherited_list() {
        _next = _prev = reinterpret_cast<Type *>(this);
    }

    Type &add(Type *new_element) {
        add_element(*new_element, *_prev, *this);
        return *this;
    }

    Type &add_front(Type *new_element) {
        add_element(*new_element, *this, *_next);
        return *this;
    }

    Type &remove() {
        _next->_prev = _prev;
        _prev->_next = _next;
        _prev = _next = reinterpret_cast<Type *>(this);
        return *_prev;
    }

    Type *next() {
        return _next == this ? nullptr : _next;
    }

    Type *prev() {
        return _prev == this ? nullptr : _prev;
    }

    bool empty() const {
        return _next == this && _next == this;
    }

    iterator begin() {
        return iterator(_next);
    }

    iterator end() {
        return iterator(reinterpret_cast<Type *>(this));
    }

};

} // namespace yacppl

