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

template <class Type, size_t Offset>
auto list_entry(list_head *head) {
    return reinterpret_cast<Type *>(reinterpret_cast<char *>(head) - reinterpret_cast<unsigned long>((reinterpret_cast<Type *>(Offset))));
}

#define list_next_entry(ptr, type, member) \
    (reinterpret_cast<type *>(reinterpret_cast<char *>((ptr)->next)-reinterpret_cast<unsigned long>(&(reinterpret_cast<type *>(0))->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member) \
    for (pos = yacppl::af_list::list_entry<typeof(*pos), offsetof(typeof(*pos), member)>((head)->next); \
            &pos->member != (head);                                     \
            pos = yacppl::af_list::list_entry<typeof(*pos), offsetof(typeof(*pos), member)>(pos->member.next))

} // namespace af_list

} // namespace yacppl

