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

} // namespace yacppl

