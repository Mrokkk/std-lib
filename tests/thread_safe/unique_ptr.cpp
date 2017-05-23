#include <thread>
#include <yatf.hpp>
#include <unique_ptr.hpp>

namespace {

yacppl::unique_ptr<int> ptr;

void thread1() {
    for (auto i = 0; i < 1024; ++i) {
        ptr = yacppl::make_unique(2);
    }
    for (auto i = 0; i < 1024; ++i) {
        auto ptr1 = yacppl::make_unique<int>(-8924);
        ptr = yacppl::move(ptr1);
    }
}

void thread2() {
    for (auto i = 0; i < 1024; ++i) {
        ptr = yacppl::make_unique(2);
    }
    for (auto i = 0; i < 1024; ++i) {
        ptr = yacppl::make_unique(2);
    }
}

} // namespace

TEST(unique_ptr, is_thread_safe) {
    for (auto i = 0; i < 1024; ++i) {
        ptr = yacppl::make_unique(2);
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

