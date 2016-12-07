#pragma once

namespace yacppl {

template<typename Type>
class unique_ptr {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer _ptr = nullptr;

public:

    constexpr unique_ptr() {}

    unique_ptr(Pointer ptr)
            : _ptr(ptr) {}

    unique_ptr(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    ~unique_ptr() {
        if (_ptr)
            delete _ptr;
    }

    unique_ptr &operator=(unique_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    }

    Pointer get() const {
        return _ptr;
    }

    Reference operator*() const {
        return *_ptr;
    }

    Pointer operator->() const {
        return _ptr;
    }

    operator Pointer() const {
        return _ptr;
    }

};

template<typename Type>
inline unique_ptr<Type> make_unique() {
    return unique_ptr<Type>(new Type);
}

template<typename Type>
inline unique_ptr<Type> make_unique(Type &&a) {
    return unique_ptr<Type>(new Type(a));
}

} // namespace yacppl

