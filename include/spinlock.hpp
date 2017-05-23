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

namespace detail {

template <int M>
class spinlock_pool {
    static spinlock pool_[32];
public:
    static spinlock &get(const void *address) {
        return pool_[reinterpret_cast<size_t>(address) % 32];
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

template <int M> spinlock spinlock_pool<M>::pool_[32];

} // namespace detail

} // namespace yacppl

