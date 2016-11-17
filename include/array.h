#pragma once

namespace yacppl {

template<typename ElementType>
class array_iterator {

    ElementType *_ptr = nullptr;

public:

    inline array_iterator() = delete;

    inline array_iterator(ElementType *ptr)
            : _ptr(ptr) {}

    inline array_iterator &operator++() {
        ++_ptr;
        return *this;
    }

    inline array_iterator operator++(int dummy) {
        (void) dummy;
        ++_ptr;
        return *this;
    }

    inline array_iterator &operator--() {
        --_ptr;
        return *this;
    }

    inline array_iterator operator--(int) {
        --_ptr;
        return *this;
    }

    inline ElementType &operator*() {
        return *_ptr;
    }

    inline ElementType *operator->() {
        return _ptr;
    }

    inline bool operator==(array_iterator<ElementType> &element) const {
        return element._ptr == _ptr;
    }

    inline bool operator!=(array_iterator<ElementType> &element) const {
        return element._ptr != _ptr;
    }

};

template<typename ElementType, unsigned int _size = 0>
class array {

    ElementType _array[_size];

public:

    inline array() {}

    inline array(std::initializer_list<ElementType> list) {
        unsigned i = 0;
        for (auto v : list)
            _array[i++] = v;
    }

    inline unsigned int size() const {
        return _size;
    }

    inline ElementType &operator[](int index) {
        return _array[index];
    }

    inline array_iterator<ElementType> begin() {
        array_iterator<ElementType> it(_array);
        return it;
    }

    inline array_iterator<ElementType> end() {
        array_iterator<ElementType> it(_array + _size);
        return it;
    }

};

} // namespace yacppl
