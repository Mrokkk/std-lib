#include <thread>
#include <yatf.hpp>
#include <shared_ptr.hpp>

yacppl::shared_ptr<int> ptr;

void thread1() {
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = nullptr;
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = ptr;
    }
    ptr = nullptr;
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = yacppl::make_shared<int>(323);
        ptr = ptr1;
        ptr1 = nullptr;
    }
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = move(ptr);
        ptr = move(ptr1);
    }
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
    for (auto i = 0u; i < 1024u; ++i) {
        auto ptr1 = move(ptr);
        ptr = move(ptr1);
    }
}

TEST(shared_ptr, is_thread_safe) {
    for (auto i = 0; i < 1024; ++i) {
        ptr = yacppl::make_shared(2);
        std::thread t1(thread1);
        std::thread t2(thread2);
        std::thread t3(thread2);
        std::thread t4(thread1);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}

