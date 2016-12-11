#pragma once

namespace yacppl {

template<typename Type>
class shared_ptr final {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer _ptr = nullptr;
    unsigned *_ref_count = nullptr;

public:

    constexpr shared_ptr() {}

    shared_ptr(Pointer ptr)
            : _ptr(ptr), _ref_count(new unsigned(1)) {}

    shared_ptr(const shared_ptr &ptr) {
        _ptr = ptr._ptr;
        _ref_count = ptr._ref_count;
        ++*_ref_count;
    }

    shared_ptr(shared_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _ref_count = other._ref_count;
        other._ref_count = nullptr;
    }

    ~shared_ptr() {
        if (_ref_count == nullptr) return;
        if (!--*_ref_count) {
            delete _ptr;
            delete _ref_count;
        }
    }

    shared_ptr &operator=(const shared_ptr &ptr) {
        _ptr = ptr._ptr;
        _ref_count = ptr._ref_count;
        ++*_ref_count;
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
        _ref_count = other._ref_count;
        other._ref_count = nullptr;
        return *this;
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

    Pointer get() const {
        return _ptr;
    }

    unsigned get_ref_count() const {
        if (_ref_count)
            return *_ref_count;
        return 0;
    }

};

template<typename Type>
inline shared_ptr<Type> make_shared() {
    return shared_ptr<Type>(new Type);
}

template<typename Type>
inline shared_ptr<Type> make_shared(Type &&a) {
    return shared_ptr<Type>(new Type(a));
}

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(args...));
}

} // namespace yacppl

