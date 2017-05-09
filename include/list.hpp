#pragma once

#include <cstddef>
#include "initializer_list.hpp"
#include "iterator.hpp"

namespace yacppl {

template<typename Type>
class list final {

    class list_element {

        Type data_;
        list_element *prev_, *next_;

    public:

        list_element() : prev_(this), next_(this) {
        }

        list_element(const Type &e) : data_(e), prev_(this), next_(this) {
        }

        auto prev() const {
            return prev_;
        }

        auto next() const {
            return next_;
        }

        auto &prev() {
            return prev_;
        }

        auto &next() {
            return next_;
        }

        auto entry() {
            return &data_;
        }

        auto entry() const {
            return &data_;
        }

    };

    list_element head_;
    size_t size_ = 0;

    list_element *back_element() const {
        return head_.prev();
    }

    list_element *front_element() const {
        return head_.next();
    }

    void add(list_element *new_elem, list_element *prev, list_element *next) {
        next->prev() = new_elem;
        prev->next() = new_elem;
        new_elem->next() = next;
        new_elem->prev() = prev;
        ++size_;
    }

    void del(list_element *prev, list_element *next) {
        auto temp = prev->next();
        next->prev() = prev;
        prev->next() = next;
        --size_;
        delete temp;
    }

    void add_front_element(list_element *new_elem) {
        add(new_elem, &head_, head_.next());
    }

    void add_back_element(list_element *new_elem) {
        add(new_elem, head_.prev(), &head_);
    }

    void delete_element(list_element *element) {
        del(element->prev(), element->next());
    }

    template <typename T>
    void copy_elements_from(const T &other) {
        for (auto it = other.cbegin(); it != other.cend(); ++it) {
            push_back(*it);
        }
    }

    template <typename T>
    void move_elements_from(T &other) {
        while (other.size_) {
            push_back(other.front());
            other.pop_front();
        }
    }

    void erase_elements(list_element *first_elem, const list_element *last_elem) {
        while (first_elem != last_elem) {
            auto temp = first_elem->prev();
            delete_element(first_elem);
            first_elem = temp->next();
        }
    }

    template <bool is_const>
    using detail_iterator = detail::iterator<list, bidirectional_iterator_tag, is_const>;

public:

    using value_type = Type;
    using node_type = list_element;
    using iterator = detail_iterator<false>;
    using const_iterator = detail_iterator<true>;

    list() = default;

    list(const std::initializer_list<Type> &list) {
        copy_elements_from(list);
    }

    template <typename Container>
    list(Container &container) {
        copy_elements_from(container);
    }

    template <typename Container>
    list(Container &&list) {
        move_elements_from(list);
    }

    ~list() {
        clear();
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_front(const Type &element) {
        add_front_element(new list_element(element));
    }

    void push_back(const Type &element) {
        add_back_element(new list_element(element));
    }

    const Type &front() const {
        return *front_element()->entry();
    }

    const Type &back() const {
        return *back_element()->entry();
    }

    iterator begin() {
        return iterator(front_element());
    }

    const_iterator begin() const {
        return const_iterator(front_element());
    }

    const_iterator cbegin() const {
        return const_iterator(front_element());
    }

    iterator end() {
        return iterator(back_element()->next());
    }

    const_iterator end() const {
        return const_iterator(back_element()->next());
    }

    const_iterator cend() const {
        return const_iterator(back_element()->next());
    }

    void pop_back() {
        erase_elements(back_element(), back_element()->next());
    }

    void pop_front() {
        erase_elements(front_element(), front_element()->next());
    }

    void clear() {
        erase_elements(front_element(), back_element()->next());
    }

    void resize(unsigned long count, Type val = Type()) {
        if (size_ < count) {
            while (size_ != count) {
                push_back(val);
            }
        } else {
            while (size_ != count) {
                pop_back();
            }
        }
    }

    void erase(iterator position) {
        erase_elements(position.node(), position.node()->next());
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

