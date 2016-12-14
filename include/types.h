#pragma once

namespace yacppl {

template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const { return value; }
    constexpr value_type operator()() const { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T&> { using type = T; };
template <typename T> struct remove_reference<T&&> { using type = T; };

template <bool B, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { using type = T; };

template <typename T, class U> struct is_same : false_type {};
template <typename T> struct is_same<T, T> : true_type {};

} // namespace yacppl

