#pragma once

namespace yacppl {

class error {

    unsigned int errno_ = 0;

public:

    constexpr error() = default;

    constexpr explicit error(unsigned int errno) : errno_(errno) {
    }

    unsigned int get() const {
        return errno_;
    }

};

template <typename value_type>
class maybe {

    error error_;
    value_type value_;
    bool has_error_;

public:

    constexpr maybe(const error &err) : error_(err), has_error_(true) {
    }

    constexpr maybe(const value_type &value) : value_(value), has_error_(false) {
    }

    operator bool() const {
        return not has_error_;
    }

    value_type &operator*() {
        return value_;
    }

    value_type &operator->() {
        return value_;
    }

    unsigned int get_error() {
        return error_.get();
    }

};

} // namespace yacppl

