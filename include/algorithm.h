#pragma once

#include "move.h"
#include "iterator.h"

namespace yacppl {

template<typename Container, typename Lambda>
inline Lambda &&for_each(Container &c, Lambda lambda) {
    for (auto &it : c) {
        lambda(it);
    }
    return move(lambda);
}

template<typename Iterator, typename Lambda>
inline Lambda &&for_each(Iterator first, Iterator last, Lambda lambda) {
    for (; first != last; ++first) {
        lambda(*first);
    }
    return move(lambda);
}

template<typename Container, typename Type>
inline int count(Container &c, Type elem) {
    auto result = 0;
    for_each(c, [&](const Type &e) { if (e == elem) result++; });
    return result;
}

template<typename Container, typename Lambda>
inline int count_if(Container &c, Lambda lambda) {
    auto result = 0;
    for_each(c, [&](const auto &e) { if (lambda(e)) result++; });
    return result;
}

template<typename Container, typename Type>
inline void fill(Container &c, const Type &e) {
    for (auto it = begin(c); it != end(c); ++it) {
        *it = e;
    }
}

template<typename Iterator, typename Type>
inline void fill(Iterator begin, Iterator end, const Type &v) {
    for (auto it = begin; it != end; ++it) {
        *it = v;
    }
}

template<typename Iterator, typename Type>
inline void fill(Iterator begin, size_t n, const Type &v) {
    for (auto i = 0u; i < n; ++begin, ++i) {
        *begin = v;
    }
}

template<typename Container>
inline void swap(Container &c1, Container &c2) {
    auto temp(move(c1));
    c1 = move(c2);
    c2 = move(temp);
}

template <typename Container, typename Value>
inline auto first_occurrence(Container &container, const Value &v) -> decltype (cbegin(container)) {
    for (auto i = cbegin(container); i != cend(container); ++i) {
        if (*i == v) {
            return i;
        }
    }
    return cend(container);
}

template <typename Iterator, typename Value>
inline Iterator first_occurrence(Iterator begin, Iterator end, const Value &v) {
    for (; begin != end; ++begin) {
        if (*begin == v) {
            return begin;
        }
    }
    return end;
}

template <typename Container, typename Value>
inline auto last_occurrence(Container &container, const Value &v) -> decltype (cbegin(container)) {
    auto last = cend(container);
    for (auto i = cbegin(container); i != cend(container); ++i) {
        if (*i == v) {
            last = i;
        }
    }
    return last;
}

template <typename Iterator, typename Value>
inline auto last_occurrence(Iterator begin, Iterator end, const Value &v) {
    auto last = end;
    for (; begin != end; ++begin) {
        if (*begin == v) {
            last = begin;
        }
    }
    return last;
}

template <typename Iterator1, typename Iterator2>
inline auto copy(Iterator1 begin1, Iterator1 end1, Iterator2 begin2, Iterator2 end2) {
    for (; begin1 != end1 || begin2 != end2; ++begin1, ++begin2) {
        *begin2 = *begin1;
    }
    return begin2;
}

} // namespace yacppl

