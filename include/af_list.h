#pragma once

// Alloc-free double-linked list

namespace yacppl {

namespace af_list {

struct list_head {
    list_head *next = this, *prev = this;

    bool empty() {
        return (next == prev);
    }

};

using list_element = list_head;

void list_init(list_head *list) {
    list->next = list->prev = list;
}

namespace detail {

void __list_add(list_head *new_element, list_head *prev, list_head *next) {
    next->prev = new_element;
    prev->next = new_element;
    new_element->next = next;
    new_element->prev = prev;
}

void __list_del(list_head *prev, list_head *next) {
    next->prev = prev;
    prev->next = next;
}

} // namespace detail

void list_del(list_head *entry) {
    detail::__list_del(entry->prev, entry->next);
    entry->next = entry;
    entry->prev = entry;
}

void list_add(list_head *new_element, list_head *head) {
    detail::__list_add(new_element, head, head->next);
}

void list_add_tail(list_head *new_element, list_head *head) {
    detail::__list_add(new_element, head->prev, head);
}
void list_move(list_head *list, list_head *head) {
    detail::__list_del(list->prev, list->next);
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

} // namespace af_list

} // namespace yacppl

