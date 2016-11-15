#pragma once

template <typename Type>
class Optional {

    Type value;

public:

    explicit Optional(Type v) : value(v) {}

};

