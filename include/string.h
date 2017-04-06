#pragma once

namespace yacppl {

namespace clib {

inline unsigned len(const char *string) {
    char *temp;
    for (temp=(char *)string; *temp!=0; temp++);
    return temp-string;
}

template <typename Container>
inline auto begin(Container &c) -> decltype (c.begin()) {
    return c.begin();
}

template <typename Container>
inline auto cbegin(const Container &c) -> decltype (c.cbegin()) {
    return c.cbegin();
}

inline auto begin(char *c) {
    return c;
}

inline auto cbegin(const char *c) {
    return c;
}

template <typename Container>
inline auto end(Container &c) -> decltype (c.end()) {
    return c.end();
}

template <typename Container>
inline auto cend(const Container &c) -> decltype (c.cend()) {
    return c.cend();
}

inline auto end(char *c) {
    return begin(c) + len(c);
}

inline auto cend(const char *c) {
    return cbegin(c) + len(c);
}

inline int compare(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

template <typename Container, typename Value>
inline auto first_occurrence(Container container, Value c) -> decltype (cbegin(container)) {
    int i, l;
    l = cend(container) - cbegin(container);
    for (i = 0; i < l; ++i) {
        if (container[i] == c) {
            return cbegin(container) + i;
        }
    }
    return cend(container);
}

template <typename Container, typename Value>
inline auto last_occurrence(Container &container, Value c) -> decltype (cbegin(container)) {
    int i, l, last = -1;
    l = cend(container) - cbegin(container);
    for (i = 0; i < l; ++i) {
        if (container[i] == c) {
            last = i;
        }
    }
    if (last != -1) {
        return cbegin(container) + last;
    }
    return cend(container);
}

} // namespace clib

} // namespace yacppl

