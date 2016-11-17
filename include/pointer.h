#pragma once

namespace yacppl {

template<typename Type>
class unique_ptr {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer _ptr = nullptr;

public:

    inline unique_ptr() {}

    inline unique_ptr(Pointer ptr)
            : _ptr(ptr) {}

    unique_ptr(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &) = delete;

    inline unique_ptr(unique_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline ~unique_ptr() {
        delete _ptr;
    }

    inline unique_ptr &operator=(unique_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }

    inline Pointer get() const {
        return _ptr;
    }

    inline Reference operator*() const {
        return *_ptr;
    }

    inline Pointer operator->() const {
        return _ptr;
    }

    inline operator Pointer() const {
        return _ptr;
    }

};

template<typename Type>
class shared_ptr {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer _ptr = nullptr;
    unsigned *_ref_count = nullptr;

public:

    inline shared_ptr() {}

    inline shared_ptr(Pointer ptr)
            : _ptr(ptr), _ref_count(new unsigned(1)) {}

    inline shared_ptr(const shared_ptr &ptr) {
        _ptr = ptr._ptr;
        _ref_count = ptr._ref_count;
        ++*_ref_count;
    }

    inline shared_ptr(shared_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _ref_count = other._ref_count;
        other._ref_count = nullptr;
    }

    inline ~shared_ptr() {
        if (_ref_count == nullptr) return;
        if (!--*_ref_count) {
            delete _ptr;
            delete _ref_count;
        }
    }

    inline shared_ptr &operator=(const shared_ptr &ptr) {
        _ptr = ptr._ptr;
        _ref_count = ptr._ref_count;
        ++*_ref_count;
        return *this;
    }

    inline shared_ptr &operator=(shared_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _ref_count = other._ref_count;
        other._ref_count = nullptr;
        return *this;
    }

    inline Reference operator*() const {
        return *_ptr;
    }

    inline Pointer operator->() const {
        return _ptr;
    }

    inline operator Pointer() const {
        return _ptr;
    }

    inline Pointer get() const {
        return _ptr;
    }

    inline unsigned get_ref_count() const {
        if (_ref_count)
            return *_ref_count;
        return 0;
    }

};

template<typename Type>
inline shared_ptr<Type> make_shared(Type &&a) {
    return shared_ptr<Type>(new Type(a));
}

template<typename Type>
inline unique_ptr<Type> make_unique(Type &&a) {
    return unique_ptr<Type>(new Type(a));
}

} // namespace yacppl
