#pragma once

namespace yacppl {

template<typename ElementType, unsigned int _size = 0>
class array {

    ElementType _array[_size];

public:

    class iterator {

        ElementType *_ptr = nullptr;

    public:

        explicit iterator(ElementType *ptr)
            : _ptr(ptr) {}

        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator++(int) {
            ++_ptr;
            return *this;
        }

        iterator &operator--() {
            --_ptr;
            return *this;
        }

        iterator operator--(int) {
            --_ptr;
            return *this;
        }

        ElementType &operator*() {
            return *_ptr;
        }

        ElementType *operator->() {
            return _ptr;
        }

        bool operator==(iterator &element) const {
            return element._ptr == _ptr;
        }

        bool operator!=(iterator &element) const {
            return element._ptr != _ptr;
        }

    };

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

    iterator begin() {
        return iterator(_array);
    }

    iterator end() {
        return iterator(_array + _size);
    }

};

} // namespace yacppl

