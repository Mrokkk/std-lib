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

};

