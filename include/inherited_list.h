#pragma once

namespace yacppl {

template <typename Type>
class inherited_list {

    Type *prev_, *next_;

    void add_element(Type &new_element, Type &prev, Type &next) {
        next.prev_ = &new_element;
        prev.next_ = &new_element;
        new_element.next_ = &next;
        new_element.prev_ = &prev;
    }

    operator Type &() {
        return *reinterpret_cast<Type *>(this);
    }

public:

    class iterator {

        Type *ptr_ = nullptr;

    public:

        constexpr iterator(Type *t)
            : ptr_(t) {}

        iterator &operator++() {
            ptr_ = ptr_->next();
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ptr_ = ptr_->next();
            return tmp;
        }

        iterator &operator--() {
            ptr_ = ptr_->prev();
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            ptr_ = ptr_->prev();
            return tmp;
        }

        Type &operator*() {
            return *ptr_;
        }

        Type *operator->() {
            return ptr_;
        }

        bool operator!=(const iterator &comp) {
            return ptr_ != comp.ptr_;
        }

    };

    constexpr inherited_list() {
        next_ = prev_ = reinterpret_cast<Type *>(this);
    }

    Type &push_back(Type *new_element) {
        add_element(*new_element, *prev_, *this);
        return *this;
    }

    Type &push_front(Type *new_element) {
        add_element(*new_element, *this, *next_);
        return *this;
    }

    Type &remove() {
        next_->prev_ = prev_;
        prev_->next_ = next_;
        prev_ = next_ = reinterpret_cast<Type *>(this);
        return *prev_;
    }

    Type *next() {
        return next_ == this ? nullptr : next_;
    }

    Type *prev() {
        return prev_ == this ? nullptr : prev_;
    }

    bool empty() const {
        return next_ == this && next_ == this;
    }

    iterator begin() {
        return iterator(next_);
    }

    iterator end() {
        return iterator(reinterpret_cast<Type *>(this));
    }

};

} // namespace yacppl

