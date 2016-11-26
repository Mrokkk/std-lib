#pragma once

template <typename Type>
struct inherited_list {

    Type *prev, *next;

    inherited_list() {
        prev = reinterpret_cast<Type *>(this);
        next = reinterpret_cast<Type *>(this);
    }

    void add_element(Type *new_element, Type *prev, Type *next) {
        next->prev = new_element;
        prev->next = new_element;
        new_element->next = next;
        new_element->prev = prev;
    }

    void add(Type *new_element) {
        add_element(new_element, prev, reinterpret_cast<Type *>(this));
    }

};

