#include <shared_ptr.hpp>
#include <thread>

yacppl::shared_ptr<int> ptr;

void atomic_increment(void *addr) {
    asm volatile("lock incl (%0)" :: "r" (addr));
}

void atomic_decrement(void *addr) {
    asm volatile("lock decl (%0)" :: "r" (addr));
}

void thread1() {
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = nullptr;
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = nullptr;
}

void thread2() {
    for (auto i = 0u; i < 2048u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = new int(4);
    for (auto i = 0u; i < 2048u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = nullptr;
}

int main() {
    ptr = yacppl::make_shared(2);
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread2);
    std::thread t4(thread1);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}

