#pragma once

namespace yacppl
{

struct error
{
    constexpr error() = default;

    constexpr explicit error(unsigned int errno)
        : errno_(errno)
    {
    }

    unsigned int get() const
    {
        return errno_;
    }

private:
    unsigned int errno_ = 0;
};

template <typename value_type>
struct maybe final
{
    constexpr maybe(const error& err)
        : error_(err)
        , has_error_(true)
    {
    }

    constexpr maybe(const value_type& value)
        : value_(value)
        , has_error_(false)
    {
    }

    operator bool() const
    {
        return not has_error_;
    }

    value_type& operator*()
    {
        return value_;
    }

    value_type& operator->()
    {
        return value_;
    }

    unsigned int get_error()
    {
        return error_.get();
    }

private:
    error error_;
    value_type value_;
    bool has_error_;
};

} // namespace yacppl
