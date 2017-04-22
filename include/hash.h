#pragma once

namespace yacppl {

template <typename Type>
struct hash {
};

template <>
struct hash<signed char> {
    unsigned operator()(signed char v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<unsigned char> {
    unsigned operator()(unsigned char v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<short> {
    unsigned operator()(short v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<unsigned short> {
    unsigned operator()(short v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<int> {
    unsigned operator()(int v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<unsigned int> {
    unsigned operator()(unsigned int v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<long> {
    unsigned operator()(long v) {
        return static_cast<unsigned>(v);
    }
};

template <>
struct hash<long long> {
    unsigned operator()(long long v) {
        return static_cast<unsigned>(v);
    }
};

} // namespace yacppl

