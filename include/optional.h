#pragma once

template <typename Type>
class optional {

    Type value;

public:

    explicit optional(Type v) : value(v) {}

};

