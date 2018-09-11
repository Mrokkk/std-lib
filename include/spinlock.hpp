#pragma once

#include <cstddef>

namespace yacppl
{

struct spinlock final
{
    enum class state : size_t
    {
        unlocked = 0,
        locked = 1
    };

    void lock();
    void unlock();

    struct scoped final
    {
        scoped(spinlock& lock)
            : lock_(lock)
        {
            lock_.lock();
        }

        ~scoped()
        {
            lock_.unlock();
        }

    private:
        spinlock& lock_;
    };

private:
    volatile state lock_ = state::unlocked;
};

inline spinlock::scoped make_scoped_lock(spinlock& lock)
{
    return spinlock::scoped(lock);
}

namespace detail
{

template <int M>
struct spinlock_pool
{
    constexpr static const size_t buckets_size = 41;

    static spinlock& get(const void* address)
    {
        return pool_[reinterpret_cast<size_t>(address) % buckets_size];
    }

    struct scoped_lock final
    {
        scoped_lock(const void* address)
            : lock_(spinlock_pool<M>::get(address))
        {
            lock_.lock();
        }

        ~scoped_lock()
        {
            lock_.unlock();
        }

    private:
        spinlock& lock_;
    };

private:
    static spinlock pool_[buckets_size];
};

template <int M> spinlock spinlock_pool<M>::pool_[spinlock_pool<M>::buckets_size];

} // namespace detail
} // namespace yacppl
