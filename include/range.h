#pragma once

#include <cstddef>

namespace yacppl {

namespace detail {

template<typename T, size_t _size = 0>
class range final {

    T *ptr_;

public:

    constexpr explicit range(T *ptr)
        : ptr_(ptr) {}

    constexpr T *begin() {
        return ptr_;
    }

    constexpr T *end() {
        return ptr_ + size();
    }

    constexpr size_t size() {
        return _size;
    }

};

template <>
class range<const char> {

    const char *ptr_;

public:

    constexpr explicit range(const char *ptr)
        : ptr_(ptr) {}

    constexpr const char *begin() {
        return ptr_;
    }

    const char *end() {
        return ptr_ + size();
    }

    size_t size() {
        return [&](){ auto s = 0u; for (; ptr_[s] != 0; ++s){}; return s; }();
    }

};

} // namespace detail

template <typename T, size_t S>
constexpr inline auto make_range(T (&ptr)[S]) {
    return detail::range<T, S>(ptr);
}

constexpr inline auto make_range(const char *ptr) {
    return detail::range<const char>(ptr);
}

constexpr inline auto make_range(char *ptr) {
    return detail::range<const char>(ptr);
}

} // namespace yacppl

