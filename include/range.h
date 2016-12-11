#pragma once

#include <cstddef>

namespace yacppl {

namespace detail {

template<typename T, size_t _size = 0>
class range final {

    T *_ptr;

public:

    constexpr explicit range(T *ptr)
        : _ptr(ptr) {}

    constexpr T *begin() {
        return _ptr;
    }

    constexpr T *end() {
        return _ptr + size();
    }

    constexpr size_t size() {
        return _size;
    }

};

template <>
class range<const char> {

    const char *_ptr;

public:

    constexpr explicit range(const char *ptr)
        : _ptr(ptr) {}

    constexpr const char *begin() {
        return _ptr;
    }

    const char *end() {
        return _ptr + size();
    }

    size_t size() {
        return [&](){ auto s = 0u; for (; _ptr[s] != 0; ++s){}; return s; }();
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

