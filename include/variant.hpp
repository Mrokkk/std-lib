#pragma once

namespace yacppl {

namespace detail {

template <typename T>
struct type {
    void set() {
    }
};

template <typename ...Types>
struct max_sizeof {
};

template <typename T>
struct max_sizeof<T> {
    static constexpr const auto value = sizeof(T);
};

template <typename T, typename ...Rest>
struct max_sizeof<T, Rest...> {
    static constexpr const auto value = sizeof(T) | max_sizeof<Rest...>::value;
};

} // namespace detail

template <typename ...Types>
struct variant : detail::type<Types>... {

    constexpr variant() : data_() {
    }

    template <typename T>
    void set(const T &value) {
        detail::type<T>::set();
        new(data_) T(value);
    }

    template <typename T>
    T &get() {
        return *reinterpret_cast<T *>(data_);
    }

private:

    char data_[detail::max_sizeof<Types...>::value];

};

} // namespace yacppl

