#pragma once

#include "move.h"

namespace yacppl {

template<typename Type>
class shared_ptr final {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer ptr_ = nullptr;
    unsigned *ref_count_ = nullptr;

    void release() {
        if (ref_count_ != nullptr) {
            if (!--*ref_count_) {
                delete ptr_;
                delete ref_count_;
            }
            ptr_ = nullptr;
            ref_count_ = nullptr;
        }
    }

public:

    shared_ptr() = default;

    shared_ptr(Pointer ptr) {
        ptr_ = ptr;
        if (ptr_) {
            ref_count_ = new unsigned(1);
        }
    }

    shared_ptr(const shared_ptr &ptr) {
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
    }

    shared_ptr(shared_ptr &&other) {
        release();
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        ref_count_ = other.ref_count_;
        other.ref_count_ = nullptr;
    }

    ~shared_ptr() {
        release();
    }

    shared_ptr &operator=(const shared_ptr &ptr) {
        release();
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&other) {
        release();
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        ref_count_ = other.ref_count_;
        other.ref_count_ = nullptr;
        return *this;
    }

    Reference operator*() const {
        return *ptr_;
    }

    Pointer operator->() const {
        return ptr_;
    }

    operator Pointer() const {
        return ptr_;
    }

    Pointer get() const {
        return ptr_;
    }

    Pointer get() {
        return ptr_;
    }

    operator bool() const {
        return ptr_ != nullptr;
    }

    bool operator==(const shared_ptr &ptr) const {
        return ptr.ptr_ == ptr_;
    }

    bool operator==(const Pointer ptr) const {
        return ptr == ptr_;
    }

    unsigned get_ref_count() const {
        if (ref_count_) {
            return *ref_count_;
        }
        return 0;
    }

};

template<typename Type>
inline shared_ptr<Type> make_shared() {
    return shared_ptr<Type>(new Type());
}

template<typename Type>
inline shared_ptr<Type> make_shared(Type &&a) {
    return shared_ptr<Type>(new Type(forward<Type>(a)));
}

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(forward<Args>(args)...));
}

} // namespace yacppl

