#pragma once

template <typename Type>
class optional final {

    Type _value;
    bool _has_value = false;

public:

    optional() = default;

    explicit optional(Type v)
            : _value(v), _has_value(true) {}

    bool has_value() const {
        return _has_value;
    }

    Type &value() {
        return _value;
    }

    Type value_or(Type a) {
        return _has_value ? _value : a;
    }

    operator bool() const {
        return _has_value;
    }

    optional &operator =(Type v) {
        _value = v;
        _has_value = true;
        return *this;
    }

    template <typename T>
    bool operator==(const T &rhs) const {
        return _has_value && rhs == _value;
    }

    bool operator==(const optional &rhs) const {
        return _has_value && rhs._has_value && rhs._value == _value;
    }

    template <typename T>
    bool operator!=(const T &rhs) const {
        return !_has_value || rhs != _value;
    }

    template <typename T>
    bool operator>(const T &rhs) const {
        return _has_value && _value > rhs;
    }

    template <typename T>
    bool operator>=(const T &rhs) const {
        return _has_value && _value >= rhs;
    }

    template <typename T>
    bool operator<(const T &rhs) const {
        return _has_value && _value < rhs;
    }

    template <typename T>
    bool operator<=(const T &rhs) const {
        return _has_value && _value <= rhs;
    }

};

