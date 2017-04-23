#pragma once

#include "initializer_list.h"
#include <cstddef>

namespace yacppl {

template<typename Type>
class list final {

    struct list_element {

        Type data;
        list_element *prev = nullptr, *next = nullptr;

        list_element() : prev(this), next(this) {
        }

        list_element(const Type &e) : data(e), prev(this), next(this) {
        }

    };

    list_element head_;
    size_t size_ = 0;

    list_element *back_element() const {
        return head_.prev;
    }

    list_element *front_element() const {
        return head_.next;
    }

    void add(list_element *new_elem, list_element *prev, list_element *next) {
        next->prev = new_elem;
        prev->next = new_elem;
        new_elem->next = next;
        new_elem->prev = prev;
        ++size_;
    }

    void del(list_element *prev, list_element *next) {
        auto temp = prev->next;
        next->prev = prev;
        prev->next = next;
        --size_;
        delete temp;
    }

    void add_front_element(list_element *new_elem) {
        add(new_elem, &head_, head_.next);
    }

    void add_back_element(list_element *new_elem) {
        add(new_elem, head_.prev, &head_);
    }

    void delete_element(list_element *element) {
        del(element->prev, element->next);
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
            auto temp = first_elem->prev;
            delete_element(first_elem);
            first_elem = temp->next;
        }
    }

public:

    class iterator {

    private:

        list_element *node_ = nullptr;

    public:

        iterator(list_element *node)
            : node_(node) {}

        list_element *node() const {
            return node_;
        }

        iterator &operator++() {
            node_ = node_->next;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        iterator &operator--() {
            node_ = node_->prev;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            node_ = node_->prev;
            return tmp;
        }

        Type &operator*() const {
            return node_->data;
        }

        Type *operator->() const {
            return &node_->data;
        }

        bool operator!=(const iterator &element) const {
            return element.node_ != node_;
        }

        bool operator==(const iterator &element) const {
            return element.node_ == node_;
        }

    };

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

    iterator begin() const {
        return iterator(front_element());
    }

    iterator end() const {
        return iterator(back_element()->next);
    }

    void pop_back() {
        erase_elements(back_element(), back_element()->next);
    }

    void pop_front() {
        erase_elements(front_element(), front_element()->next);
    }

    void clear() {
        erase_elements(front_element(), back_element()->next);
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
        erase_elements(position.node(), position.node()->next);
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

