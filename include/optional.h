#pragma once

template <typename Type>
class optional {

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

    operator Type() const {
        return _value;
    }

    operator bool() const {
        return _has_value;
    }

};

