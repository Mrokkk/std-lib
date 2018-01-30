#pragma once

#include "move.hpp"
#include "atomic.hpp"
#include "spinlock.hpp"

namespace yacppl {

template<typename Type>
class shared_ptr final {

    using Reference = Type &;
    using Pointer = Type *;

    Pointer ptr_ = nullptr;
    unsigned *ref_count_ = nullptr;
    static spinlock spinlock_;

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

    explicit shared_ptr(Pointer ptr) : ptr_(ptr) {
        if (ptr_) {
            ref_count_ = new unsigned(1);
        }
    }

    shared_ptr(const shared_ptr &ptr) {
        auto _ = make_scoped_lock(spinlock_);
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> &ptr) {
        auto _ = make_scoped_lock(spinlock_);
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
    }

    shared_ptr(shared_ptr &&other) {
        auto _ = make_scoped_lock(spinlock_);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        ref_count_ = other.ref_count_;
        other.ref_count_ = nullptr;
    }

    ~shared_ptr() {
        auto _ = make_scoped_lock(spinlock_);
        release();
    }

    shared_ptr &operator=(Pointer ptr) {
        auto _ = make_scoped_lock(spinlock_);
        release();
        ptr_ = ptr;
        if (ptr_) {
            ref_count_ = new unsigned(1);
        }
        return *this;
    }

    shared_ptr &operator=(const shared_ptr &ptr) {
        auto _ = make_scoped_lock(spinlock_);
        release();
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
        return *this;
    }

    template <typename U>
    shared_ptr &operator=(const shared_ptr<U> &ptr) {
        auto _ = make_scoped_lock(spinlock_);
        release();
        ptr_ = ptr.ptr_;
        if (ptr.ref_count_ != nullptr) {
            ref_count_ = ptr.ref_count_;
            ++*ref_count_;
        }
        return *this;
    }

    shared_ptr &operator=(shared_ptr &&other) {
        auto _ = make_scoped_lock(spinlock_);
        release();
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        ref_count_ = other.ref_count_;
        other.ref_count_ = nullptr;
        return *this;
    }

    template <typename T>
    void reset(T v) {
        operator=(v);
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

    bool operator!=(const shared_ptr &ptr) const {
        return ptr.ptr_ != ptr_;
    }

    bool operator!=(const Pointer ptr) const {
        return ptr != ptr_;
    }

    unsigned get_ref_count() const {
        if (ref_count_) {
            return *ref_count_;
        }
        return 0;
    }

    template <class U>
    friend class shared_ptr;
};

template <typename T> spinlock shared_ptr<T>::spinlock_;

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

