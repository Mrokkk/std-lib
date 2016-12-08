#pragma once

#include <cstddef>

namespace yacppl {

template<typename T, size_t _size = 0>
class range {

    T *_ptr;

public:

    constexpr explicit range(T *ptr)
        : _ptr(ptr) {}

    constexpr T *begin() {
        return _ptr;
    }

    constexpr T *end() {
        return _size > 0 ? _ptr + _size : _ptr + size();
    }

    constexpr size_t size() {
        return _size > 0 ? _size : [&](){ auto s = 0u; for (; _ptr[s] != 0; ++s){}; return s; }();
    }

};

template <typename T, size_t S>
constexpr inline auto make_range(T (&ptr)[S]) {
    return range<T, S>(ptr);
}

constexpr inline auto make_range(char *ptr) {
    return range<char>(ptr);
}

constexpr inline auto make_range(const char *ptr) {
    return range<const char>(ptr);
}

} // namespace yacppl

