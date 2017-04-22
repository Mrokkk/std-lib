#pragma once

namespace yacppl {

template <typename T1, typename T2>
struct pair {

    T1 first;
    T2 second;

    pair(const T1 &v1, const T2 &v2) : first(v1), second(v2) {
    }

};

} // namespace yacppl
