#pragma once

namespace yacppl {

template <typename T1, typename T2>
struct pair {

    T1 first;
    T2 second;

    constexpr pair() : first(), second() {
    }

    constexpr pair(const T1 &v1, const T2 &v2) : first(v1), second(v2) {
    }

    bool operator==(const pair &p) const {
        return p.first == first && p.second == second;
    }

    bool operator!=(const pair &p) const {
        return !operator==(p);
    }

};

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1 &v1, const T2 &v2) {
    return pair<T1, T2>(v1, v2);
}

} // namespace yacppl
