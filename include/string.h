#pragma once

namespace yacppl {

inline unsigned length(const char *string) {
    const char *temp;
    for (temp = string; *temp != 0; ++temp);
    return temp-string;
}

inline auto begin(char *c) {
    return c;
}

inline auto cbegin(const char *c) {
    return c;
}

inline auto end(char *c) {
    return begin(c) + length(c);
}

inline auto cend(const char *c) {
    return cbegin(c) + length(c);
}

inline int compare(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

} // namespace yacppl

