#pragma once

#include <cstddef>

namespace yacppl {

struct spinlock {

    enum class state : size_t {
        unlocked = 0,
        locked = 1
    };

    void lock();
    void unlock();

    class scoped {

        spinlock &lock_;

    public:

        scoped(spinlock &lock) : lock_(lock) {
            lock_.lock();
        }

        ~scoped() {
            lock_.unlock();
        }

    };

private:

    volatile state lock_ = state::unlocked;

};

inline spinlock::scoped make_scoped_lock(spinlock &lock) {
    return spinlock::scoped(lock);
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

