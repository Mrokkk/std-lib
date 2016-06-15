//
// Created by maciek on 14.06.16.
//

#pragma once

namespace std
{
template<typename __T>
class initializer_list
{
    const __T *__array;
    unsigned int __size;

    initializer_list(const __T *__a, unsigned int __l)
        : __array(__a), __size(__l)
    { }

public:
    initializer_list()
        : __array(0), __size(0)
    { }

    unsigned int size() const
    {
        return __size;
    }

    const __T *begin() const
    {
        return __array;
    }

    const __T *end() const
    {
        return  &__array[__size];
    }

};
}