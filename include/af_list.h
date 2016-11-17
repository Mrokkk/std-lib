#pragma once

// Alloc-free double-linked list

namespace yacppl {

struct list_head {
    list_head *next = this, *prev = this;
};

inline void list_init(list_head *list) {
    list->next = list->prev = list;
}

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

inline void list_add(list_head *new_element, list_head *head) {
    __list_add(new_element, head, head->next);
}

inline void list_add_tail(list_head *new_element, list_head *head) {
    __list_add(new_element, head->prev, head);
}

inline int list_empty(list_head *entry) {
    return (entry->next == entry);
}

inline void list_del(list_head *entry) {
    __list_del(entry->prev, entry->next);
    entry->next = entry;
    entry->prev = entry;
}

inline void list_move(list_head *list, list_head *head) {
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_next_entry(ptr, type, member) \
    ((type *)((char *)((ptr)->next)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, typeof(*pos), member);          \
            &pos->member != (head);                                     \
            pos = list_entry(pos->member.next, typeof(*pos), member))

} // namespace yacppl

