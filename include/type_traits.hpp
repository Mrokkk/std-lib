#pragma once

namespace yacppl {

using nullptr_t = decltype(nullptr);

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

template <typename T>
struct is_integral : integral_constant<
     bool,
     is_same<bool, typename remove_const<T>::type>::value ||
     is_same<char, typename remove_const<T>::type>::value ||
     is_same<signed char, typename remove_const<T>::type>::value ||
     is_same<unsigned char, typename remove_const<T>::type>::value ||
     is_same<short, typename remove_const<T>::type>::value ||
     is_same<unsigned short, typename remove_const<T>::type>::value ||
     is_same<int, typename remove_const<T>::type>::value ||
     is_same<unsigned int, typename remove_const<T>::type>::value ||
     is_same<long, typename remove_const<T>::type>::value ||
     is_same<unsigned long, typename remove_const<T>::type>::value ||
     is_same<long long, typename remove_const<T>::type>::value> {
};

template <typename T>
struct is_floating_point : integral_constant<
     bool,
     is_same<float, typename remove_const<T>::type>::value ||
     is_same<double, typename remove_const<T>::type>::value ||
     is_same<long double, typename remove_const<T>::type>::value> {
};

template <typename T>
struct is_arithmetic : integral_constant<
    bool, is_integral<T>::value || is_floating_point<T>::value> {
};

namespace detail {

template <typename T, bool = is_arithmetic<T>::value>
struct is_unsigned : integral_constant<bool, T(0) < T(-1)> {};

template <typename T>
struct is_unsigned<T, false> : false_type {};

template <typename T, bool = is_arithmetic<T>::value>
struct is_signed : integral_constant<bool, T(-1) < T(0)> {};

template <typename T>
struct is_signed<T, false> : false_type {};

} // namespace detail

template <typename T>
struct is_unsigned : detail::is_unsigned<T>::type {};

template <typename T>
struct is_signed : detail::is_signed<T>::type {};

template <typename T> struct is_pointer_helper : false_type {};
template <typename T> struct is_pointer_helper<T*> : true_type {};
template <typename T> struct is_pointer : is_pointer_helper<typename remove_const<T>::type> {};

template <typename T>
struct is_void {
    static const bool value = false;
};

template<>
struct is_void<void> {
    static const bool value = true;
};

template <bool B, class T, class F>
struct conditional { typedef T type; };

template <class T, class F>
struct conditional<false, T, F> { typedef F type; };

} // namespace yacppl

