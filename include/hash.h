#pragma once

namespace yacppl {

template <typename Type>
struct hash {
    unsigned operator()(const Type &v) {
        return reinterpret_cast<unsigned>(v);
    }
};

template <>
struct hash<int> {
    unsigned operator()(int v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<short> {
    unsigned operator()(short v) {
        return static_cast<unsigned>(v);
    }
};

} // namespace yacppl

