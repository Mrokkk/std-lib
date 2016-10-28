#pragma once

#include <Move.h>

template <typename Container, typename Lambda>
inline Lambda &&for_each(Container &c, Lambda lambda) {
    for (auto &it : c)
        lambda(it);
    return move(lambda);
}

template <typename Iterator, typename Lambda>
inline Lambda &&for_each(Iterator first, Iterator last, Lambda lambda) {
    for (; first != last; ++first)
        lambda(*first);
    return move(lambda);
}

template <typename Container, typename Type>
inline int count(Container &c, Type elem) {
    auto result = 0;
    for_each(c, [ & ](const Type &e) { if (e == elem) result++; });
    return result;
};

template <typename Container, typename Lambda>
inline int count_if(Container &c, Lambda lambda) {
    auto result = 0;
    for_each(c, [ & ](const auto &e) { if (lambda(e)) result++; });
    return result;
};

template <typename Container, typename Type>
inline void fill(Container &c, const Type &e) {
    for (auto &i : c)
        i = e;
};

template <typename Container>
inline void swap(Container &c1, Container &c2) {
    auto temp(move(c1));
    c1 = move(c2);
    c2 = move(temp);
}
