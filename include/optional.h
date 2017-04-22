#pragma once

template <typename Type>
class optional final {

    Type value_;
    bool has_value_ = false;

public:

    optional() = default;

    optional(Type v) : value_(v), has_value_(true) {
    }

    bool has_value() const {
        return has_value_;
    }

    Type &value() {
        return value_;
    }

    Type value_or(Type a) {
        return has_value_ ? value_ : a;
    }

    operator bool() const {
        return has_value_;
    }

    optional &operator=(Type v) {
        value_ = v;
        has_value_ = true;
        return *this;
    }

    template <typename T>
    bool operator==(const T &rhs) const {
        return has_value_ && rhs == value_;
    }

    bool operator==(const optional &rhs) const {
        if (has_value_ && rhs.has_value_) {
            return rhs.value_ == value_;
        }
        else if (!has_value_ && !rhs.has_value_) {
            return true;
        }
        return false;
    }

    template <typename T>
    bool operator!=(const T &rhs) const {
        return !operator==(rhs);
    }

    bool operator!=(const optional &rhs) const {
        return !operator==(rhs);
    }

    template <typename T>
    bool operator>(const T &rhs) const {
        return has_value_ && value_ > rhs;
    }

    template <typename T>
    bool operator>=(const T &rhs) const {
        return has_value_ && value_ >= rhs;
    }

    template <typename T>
    bool operator<(const T &rhs) const {
        return has_value_ && value_ < rhs;
    }

    template <typename T>
    bool operator<=(const T &rhs) const {
        return has_value_ && value_ <= rhs;
    }

};

