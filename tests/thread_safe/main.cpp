#define YATF_MAIN
#include <cstdio>
#include <yatf.hpp>
#include <spinlock.hpp>

void atomic_increment(void *addr) {
    asm volatile("lock incl (%0)" :: "r" (addr));
}

void atomic_decrement(void *addr) {
    asm volatile("lock decl (%0)" :: "r" (addr));
}

void spinlock_lock(volatile size_t *lock) {
    size_t dummy = SPINLOCK_LOCKED;
    asm volatile(R"(
        1: lock xchg %0, %1
        test %1, %1
        jnz 1b)"
        : "=m" (*lock)
        : "r" (dummy)
        : "memory");
}

void spinlock_unlock(volatile size_t *lock) {
    size_t dummy = SPINLOCK_UNLOCKED;
    asm volatile(
        "lock xchg %0, %1"
        : "=m" (*lock)
        : "r" (dummy)
        : "memory");
}

int main(int argc, const char *argv[]) {
    return yatf::main(printf, argc, argv);
}

