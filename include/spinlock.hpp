#pragma once

#include <cstddef>

void spinlock_unlock(volatile size_t *lock);
void spinlock_lock(volatile size_t *lock);

namespace yacppl {

#define SPINLOCK_UNLOCKED   0
#define SPINLOCK_LOCKED     1

class spinlock {
    volatile size_t lock_ = SPINLOCK_UNLOCKED;
public:
    void lock() {
        ::spinlock_lock(&lock_);
    }
    void unlock() {
        ::spinlock_unlock(&lock_);
    }
};

class scoped_lock {
    spinlock &lock_;
public:
    scoped_lock(spinlock &lock) : lock_(lock) {
        lock_.lock();
    }
    ~scoped_lock() {
        lock_.unlock();
    }
};

inline scoped_lock make_scoped_lock(spinlock &lock) {
    return scoped_lock(lock);
}

namespace detail {

template <int M>
struct spinlock_pool {

    constexpr static const size_t buckets_size = 41;

private:

    static spinlock pool_[buckets_size];

public:

    static spinlock &get(const void *address) {
        return pool_[reinterpret_cast<size_t>(address) % buckets_size];
    }

    class scoped_lock {
        spinlock &lock_;
    public:
        scoped_lock(const void *address) : lock_(spinlock_pool<M>::get(address)) {
            lock_.lock();
        }
        ~scoped_lock() {
            lock_.unlock();
        }
    };

};

template <int M> spinlock spinlock_pool<M>::pool_[spinlock_pool<M>::buckets_size];

} // namespace detail

} // namespace yacppl

