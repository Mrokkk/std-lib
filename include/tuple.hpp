#pragma once

#include <cstddef>

namespace yacppl
{
namespace detail
{

template <size_t ...N>
struct expand
{
    using type = expand<N...>;
};

template <size_t N, typename ...T>
struct choose_nth
{
};

template <size_t N, typename T, typename ...U>
struct choose_nth<N, T, U...> : choose_nth<N - 1, U...>
{
};

template <typename T, typename ...U>
struct choose_nth<0, T, U...>
{
    using type = T;
};

template <size_t N, typename T>
struct tuple_element
{
    explicit tuple_element(const T& val)
        : value_(val)
    {
    }

    const T& get() const
    {
        return value_;
    }

private:
    const T value_;
};

template <size_t L, size_t I = 0, typename S = expand<>>
struct range
{
};

template <size_t L, size_t I, size_t ...N>
struct range<L, I, expand<N...>> : range<L, I + 1, expand<N..., I>>
{
};

template <size_t L, size_t ...N>
struct range<L, L, expand<N...>> : expand<N...>
{
};

template <typename N, typename ...T>
class tuple_impl
{
};

template <size_t ...N, typename ...T>
struct tuple_impl<expand<N...>, T...> : public tuple_element<N, T>...
{
    template <size_t M> using value_type = typename choose_nth<M, T...>::type;

    explicit tuple_impl(const T&... values)
        : tuple_element<N, T>(values)...
    {
    }

    template <size_t M>
    const value_type<M>& get() const
    {
        return tuple_element<M, value_type<M>>::get();
    }
};

} // namespace detail

template <typename ...T>
struct tuple : public detail::tuple_impl<typename detail::range<sizeof...(T)>::type, T...>
{
    explicit tuple(const T&... values)
        : detail::tuple_impl<typename detail::range<sizeof...(T)>::type, T...>(values...)
    {
    }

    static constexpr std::size_t size()
    {
        return sizeof...(T);
    }
};

} // namespace yacppl
