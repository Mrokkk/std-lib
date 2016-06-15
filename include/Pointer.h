//
// Created by maciek on 10.06.16.
//

#pragma once

template <typename Type>
class UniquePointer
{
private:
    Type *_ptr = nullptr;

public:

    constexpr inline UniquePointer()
    { }

    constexpr inline UniquePointer(Type *ptr)
        : _ptr(ptr)
    { }

    UniquePointer(const UniquePointer &) = delete;

    UniquePointer(UniquePointer &) = delete;

    inline UniquePointer(UniquePointer &&other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline ~UniquePointer()
    {
        delete _ptr;
    }

    inline UniquePointer &operator =(UniquePointer &&other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline Type *get() const
    {
        return _ptr;
    }

    inline Type operator *()
    {
        return *_ptr;
    }

    inline Type *operator ->()
    {
        return _ptr;
    }

    inline operator Type *()
    {
        return _ptr;
    }

};

template <typename Type>
class SharedPointer
{

private:
    Type *_ptr = nullptr;
    unsigned *_refCount = nullptr;

public:

    constexpr inline SharedPointer()
    { }

    constexpr inline SharedPointer(Type *ptr)
        : _ptr(ptr), _refCount(new unsigned(1))
    { }

    inline SharedPointer(const SharedPointer &ptr)
    {
        _ptr = ptr._ptr;
        _refCount = ptr._refCount;
        ++*_refCount;
    }

    inline ~SharedPointer()
    {
        if (_refCount == nullptr) return;
        if (!--*_refCount)
        {
            delete _ptr;
            delete _refCount;
        }
    }

    inline SharedPointer &operator =(const SharedPointer &ptr)
    {
        _ptr = ptr._ptr;
        _refCount = ptr._refCount;
        ++*_refCount;
        return *this;
    }

    inline Type &operator *()
    {
        return *_ptr;
    }

    inline Type *operator ->()
    {
        return _ptr;
    }

    inline operator Type *()
    {
        return _ptr;
    }

    inline Type *get() const
    {
        return _ptr;
    }

    inline unsigned getRefCount()
    {
        if (_refCount)
            return *_refCount;
        return 0;
    }

};

template <typename Type>
inline SharedPointer<Type> makeShared(Type &&a)
{
    return SharedPointer<Type>(new Type(a));
}

template <typename Type>
inline UniquePointer<Type> makeUnique(Type &&a)
{
    return UniquePointer<Type>(new Type(a));
}
