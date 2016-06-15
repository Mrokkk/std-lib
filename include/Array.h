//
// Created by maciek on 12.06.16.
//

#pragma once

template <typename ElementType>
class ArrayIterator
{
private:
    ElementType *_ptr = nullptr;

public:

    inline ArrayIterator() = delete;

    inline ArrayIterator(ElementType *ptr)
        : _ptr(ptr)
    { }

    inline ArrayIterator &operator ++()
    {
        ++_ptr;
        return *this;
    }

    inline ArrayIterator operator ++(int dummy)
    {
        (void) dummy;
        ++_ptr;
        return *this;
    }

    inline ArrayIterator &operator --()
    {
        --_ptr;
        return *this;
    }

    inline ArrayIterator operator --(int dummy)
    {
        (void) dummy;
        --_ptr;
        return *this;
    }

    inline ElementType &operator *()
    {
        return *_ptr;
    }

    inline ElementType *operator ->()
    {
        return _ptr;
    }

    inline bool operator ==(ArrayIterator<ElementType> &element) const
    {
        return element._ptr == _ptr;
    }

    inline bool operator !=(ArrayIterator<ElementType> &element) const
    {
        return element._ptr != _ptr;
    }

};

template <typename ElementType, unsigned int _size = 0>
class Array
{
private:

    ElementType _array[_size];

public:

    inline Array()
    { }

    inline Array(std::initializer_list<ElementType> list)
    {
        unsigned i = 0;
        for (auto v : list)
            _array[i++] = v;
    }

    inline unsigned int size() const
    {
        return _size;
    }

    inline ElementType &operator [](int index)
    {
        return _array[index];
    }

    inline ArrayIterator<ElementType> begin()
    {
        ArrayIterator<ElementType> it(_array);
        return it;
    }

    inline ArrayIterator<ElementType> end()
    {
        ArrayIterator<ElementType> it(_array + _size);
        return it;
    }

};


