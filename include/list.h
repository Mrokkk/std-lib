#pragma once

#include <cstddef>
#include "initializer_list.h"
#include "iterator.h"

namespace yacppl {

template<typename Type>
class list final {

    struct list_element {

        Type data;
        list_element *prev_ = nullptr, *next_ = nullptr;

        list_element() : prev_(this), next_(this) {
        }

        list_element(const Type &e) : data(e), prev_(this), next_(this) {
        }

        auto prev() {
            return prev_;
        }

        auto next() {
            return next_;
        }

        auto entry() {
            return &data;
        }

    };

    list_element head_;
    size_t size_ = 0;

    list_element *back_element() const {
        return head_.prev_;
    }

    list_element *front_element() const {
        return head_.next_;
    }

    void add(list_element *new_elem, list_element *prev, list_element *next) {
        next->prev_ = new_elem;
        prev->next_ = new_elem;
        new_elem->next_ = next;
        new_elem->prev_ = prev;
        ++size_;
    }

    void del(list_element *prev, list_element *next) {
        auto temp = prev->next_;
        next->prev_ = prev;
        prev->next_ = next;
        --size_;
        delete temp;
    }

    void add_front_element(list_element *new_elem) {
        add(new_elem, &head_, head_.next_);
    }

    void add_back_element(list_element *new_elem) {
        add(new_elem, head_.prev_, &head_);
    }

    void delete_element(list_element *element) {
        del(element->prev_, element->next_);
    }

    template<typename T>
    void copy_elements_from(const T &other) {
        for (const auto &e : other)
            push_back(e);
    }

    void move_elements_from(list &other) {
        while (other.size_) {
            push_back(other.front());
            other.pop_front();
        }
    }

    void erase_elements(list_element *first_elem, const list_element *last_elem) {
        while (first_elem != last_elem) {
            auto temp = first_elem->prev_;
            delete_element(first_elem);
            first_elem = temp->next_;
        }
    }

    template <bool is_const>
    using detail_iterator = list_iterator<Type, list_element, is_const>;

public:

    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    list() = default;

    list(const std::initializer_list<Type> &list) {
        copy_elements_from(list);
    }

    list(const list &list) {
        copy_elements_from(list);
    }

    list(list &&list) {
        move_elements_from(list);
    }

    ~list() {
        clear();
    }

    size_t size() const {
        return size_;
    }

    void push_front(const Type &element) {
        add_front_element(new list_element(element));
    }

    void push_back(const Type &element) {
        add_back_element(new list_element(element));
    }

    const Type &front() const {
        return front_element()->data;
    }

    const Type &back() const {
        return back_element()->data;
    }

    const_iterator cbegin() const {
        return const_iterator(front_element());
    }

    const_iterator cend() const {
        return const_iterator(back_element()->next_);
    }

    iterator begin() const {
        return iterator(front_element());
    }

    iterator end() const {
        return iterator(back_element()->next_);
    }

    void pop_back() {
        erase_elements(back_element(), back_element()->next_);
    }

    void pop_front() {
        erase_elements(front_element(), front_element()->next_);
    }

    void clear() {
        erase_elements(front_element(), back_element()->next_);
    }

    void resize(unsigned long count, Type val = Type()) {
        if (size_ < count) {
            while (size_ != count)
                push_back(val);
        } else {
            while (size_ != count)
                pop_back();
        }
    }

    void erase(iterator position) {
        erase_elements(position.node(), position.node()->next_);
    }

    void erase(const iterator &first, const iterator &last) {
        erase_elements(first.node(), last.node());
    }

    list &operator=(const list &other) {
        clear();
        copy_elements_from(other);
        return *this;
    }

    list &operator=(list &&other) {
        clear();
        move_elements_from(other);
        return *this;
    }

};

} // namespace yacppl

