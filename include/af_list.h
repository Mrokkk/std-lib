#pragma once

#include <stddef.h>

// Alloc-free double-linked list

namespace yacppl {

namespace af_list {

struct list_head {

    list_head *next = this, *prev = this;

    bool empty() const {
        return (prev == this) && (next == this);
    }

};

template <class Type>
class af_list {

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

public:

    af_list *next = this, *prev = this;

    void add(af_list *new_element) {
        __list_add(new_element, prev, this);
    }

    void del() {
        __list_del(prev, next);
        next = this;
        prev = this;
    }

    bool empty() const {
        return (prev == this) && (next == this);
    }

    auto entry(af_list *head, size_t Offset) {
        return reinterpret_cast<Type *>(reinterpret_cast<char *>(head) - reinterpret_cast<unsigned long>((reinterpret_cast<Type *>(Offset))));
    }

    template <typename Member, typename Func>
    void for_each_entry(Member Type::* m, Func lambda) {
        auto offset = offset_of(m);
        for (auto it = entry(next, offset); &(it->*m) != this; it = entry(reinterpret_cast<af_list *>(reinterpret_cast<char *>(it) + offset)->next, offset)) {
            lambda(it);
        }
    }

};

using list_element = list_head;

inline void list_init(list_head *list) {
    list->next = list->prev = list;
}

namespace detail {

inline void __list_add(list_head *new_element, list_head *prev, list_head *next) {
    next->prev = new_element;
    prev->next = new_element;
    new_element->next = next;
    new_element->prev = prev;
}

inline void __list_del(list_head *prev, list_head *next) {
    next->prev = prev;
    prev->next = next;
}

} // namespace detail

inline void list_del(list_head *entry) {
    detail::__list_del(entry->prev, entry->next);
    entry->next = entry;
    entry->prev = entry;
}

inline void list_add(list_head *new_element, list_head *head) {
    detail::__list_add(new_element, head, head->next);
}

inline void list_add_tail(list_head *new_element, list_head *head) {
    detail::__list_add(new_element, head->prev, head);
}

inline void list_move(list_head *list, list_head *head) {
    detail::__list_del(list->prev, list->next);
    list_add_tail(list, head);
}

template <class Type>
auto list_entry(list_head *head, size_t Offset) {
    return reinterpret_cast<Type *>(reinterpret_cast<char *>(head) - reinterpret_cast<unsigned long>((reinterpret_cast<Type *>(Offset))));
}

template<typename T, typename U>
constexpr size_t offset_of(U T::*member) {
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template <class Type, class Member, typename Func>
void list_for_each_entry(yacppl::af_list::list_head *head, Member Type::* m, Func lambda) {
    auto offset = offset_of(m);
    for (auto it = list_entry<Type>(head->next, offset); &(it->*m) != head; it = list_entry<Type>(reinterpret_cast<list_head *>(reinterpret_cast<char *>(it) + offset)->next, offset)) {
        lambda(it);
    }
}

#define list_next_entry(ptr, type, member) \
    (reinterpret_cast<type *>(reinterpret_cast<char *>((ptr)->next)-reinterpret_cast<unsigned long>(&(reinterpret_cast<type *>(0))->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

} // namespace af_list

} // namespace yacppl

