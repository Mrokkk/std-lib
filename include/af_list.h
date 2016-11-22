#pragma once

#include <stddef.h>

// Alloc-free double-linked list

namespace yacppl {

template <class Type>
class af_list {

    af_list *next = this, *prev = this;
    size_t offset;

    void __list_add(af_list *new_element, af_list *prev, af_list *next) {
        next->prev = new_element;
        prev->next = new_element;
        new_element->next = next;
        new_element->prev = prev;
    }

    void __list_del(af_list *prev, af_list *next) {
        next->prev = prev;
        prev->next = next;
    }

    template <typename T, typename U>
    constexpr size_t offset_of(U T::*member) {
        return (char *)&((T *)nullptr->*member) - (char *)nullptr;
    }

public:

    af_list() {}

    template <typename U>
    explicit af_list(U Type::*member) {
        offset = offset_of(member);
    }

    void add(af_list *new_element) {
        __list_add(new_element, prev, this);
    }

    void add_front(af_list *new_element) {
        __list_add(new_element, this, next);
    }

    void del() {
        __list_del(prev, next);
        next = this;
        prev = this;
    }

    bool empty() const {
        return (prev == this) && (next == this);
    }

    auto entry() {
        return reinterpret_cast<Type *>(reinterpret_cast<char *>(this) - reinterpret_cast<unsigned long>((reinterpret_cast<Type *>(offset))));
    }

    template <typename Func>
    void for_each_entry(Func lambda) {
        for (auto it = next->entry(); reinterpret_cast<af_list *>(reinterpret_cast<char *>(it) + offset) != this; it = reinterpret_cast<af_list *>(reinterpret_cast<char *>(it) + offset)->next->entry()) {
            lambda(it);
        }
    }

};

template <typename T>
using af_list_element = af_list<T>;

#if 0
inline void list_move(list_head *list, list_head *head) {
    detail::__list_del(list->prev, list->next);
    list_add_tail(list, head);
}

#define list_next_entry(ptr, type, member) \
    (reinterpret_cast<type *>(reinterpret_cast<char *>((ptr)->next)-reinterpret_cast<unsigned long>(&(reinterpret_cast<type *>(0))->member)))
#endif

} // namespace yacppl

