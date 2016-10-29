#pragma once

template <typename Type>
class UniquePointer {

    using Reference = Type &;
    using Pointer = Type *;

private:

    Pointer _ptr = nullptr;

public:

    inline UniquePointer()
    { }

    inline UniquePointer(Pointer ptr)
        : _ptr(ptr)
    { }

    UniquePointer(const UniquePointer &) = delete;

    UniquePointer(UniquePointer &) = delete;

    inline UniquePointer(UniquePointer &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline ~UniquePointer() {
        delete _ptr;
    }

    inline UniquePointer &operator =(UniquePointer &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }

    inline Pointer get() const {
        return _ptr;
    }

    inline Reference operator *() const {
        return *_ptr;
    }

    inline Pointer operator ->() const {
        return _ptr;
    }

    inline operator Pointer() const {
        return _ptr;
    }

};

template <typename Type>
class SharedPointer {

    using Reference = Type &;
    using Pointer = Type *;

private:

    Pointer _ptr = nullptr;
    unsigned *_refCount = nullptr;

public:

    inline SharedPointer()
    { }

    inline SharedPointer(Pointer ptr)
        : _ptr(ptr), _refCount(new unsigned(1))
    { }

    inline SharedPointer(const SharedPointer &ptr) {
        _ptr = ptr._ptr;
        _refCount = ptr._refCount;
        ++*_refCount;
    }

    inline SharedPointer(SharedPointer &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _refCount = other._refCount;
        other._refCount = nullptr;
    }

    inline ~SharedPointer() {
        if (_refCount == nullptr) return;
        if (!--*_refCount) {
            delete _ptr;
            delete _refCount;
        }
    }

    inline SharedPointer &operator =(const SharedPointer &ptr) {
        _ptr = ptr._ptr;
        _refCount = ptr._refCount;
        ++*_refCount;
        return *this;
    }

    inline SharedPointer &operator =(SharedPointer &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _refCount = other._refCount;
        other._refCount = nullptr;
        return *this;
    }

    inline Reference operator *() const {
        return *_ptr;
    }

    inline Pointer operator ->() const {
        return _ptr;
    }

    inline operator Pointer() const {
        return _ptr;
    }

    inline Pointer get() const {
        return _ptr;
    }

    inline unsigned getRefCount() const {
        if (_refCount)
            return *_refCount;
        return 0;
    }

};

template <typename Type>
inline SharedPointer<Type> makeShared(Type &&a) {
    return SharedPointer<Type>(new Type(a));
}

template <typename Type>
inline UniquePointer<Type> makeUnique(Type &&a) {
    return UniquePointer<Type>(new Type(a));
}

