#pragma once

namespace yacppl {

template<typename ElementType>
class array_iterator {

    ElementType *_ptr = nullptr;

public:

    array_iterator() = delete;

    array_iterator(ElementType *ptr)
            : _ptr(ptr) {}

    array_iterator &operator++() {
        ++_ptr;
        return *this;
    }

    array_iterator operator++(int dummy) {
        (void) dummy;
        ++_ptr;
        return *this;
    }

    array_iterator &operator--() {
        --_ptr;
        return *this;
    }

    array_iterator operator--(int) {
        --_ptr;
        return *this;
    }

    ElementType &operator*() {
        return *_ptr;
    }

    ElementType *operator->() {
        return _ptr;
    }

    bool operator==(array_iterator<ElementType> &element) const {
        return element._ptr == _ptr;
    }

    bool operator!=(array_iterator<ElementType> &element) const {
        return element._ptr != _ptr;
    }

};

template<typename ElementType, unsigned int _size = 0>
class array {

    ElementType _array[_size];

public:

    array() {}

    array(std::initializer_list<ElementType> list) {
        unsigned i = 0;
        for (auto v : list)
            _array[i++] = v;
    }

    unsigned int size() const {
        return _size;
    }

    ElementType &operator[](int index) {
        return _array[index];
    }

    array_iterator<ElementType> begin() {
        array_iterator<ElementType> it(_array);
        return it;
    }

    array_iterator<ElementType> end() {
        array_iterator<ElementType> it(_array + _size);
        return it;
    }

};

} // namespace yacppl

