#pragma once

namespace yacppl {

inline int strcmp(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

inline unsigned strlen(const char *string) {
    char *temp;
    for (temp=(char *)string; *temp!=0; temp++);
    return temp-string;
}

inline char *strchr(const char *string, int c) {
    int i, len;
    if (string == 0) return 0;
    len = strlen(string);
    for (i = 0; i < len; ++i) {
        if (string[i] == (char)c) {
            return (char *)&string[i];
        }
    }
    return 0;
}

inline char *strrchr(const char *string, int c) {
    int i, len, last = -1;
    if (string == 0) return 0;
    len = strlen(string);
    for (i = 0; i < len; ++i) {
        if (string[i] == (char)c) {
            last = i;
        }
    }
    if (last != -1) {
        return (char *)&string[last];
    }
    return 0;
}

class path {

    static const constexpr unsigned initial_size_ = 256;

    char *path_;
    char *it_;

    char *remove_trailing_slash(char *start, char *end) {
        end--;
        while (end != start) {
            if (*end != '/') {
                return end + 1;
            }
            else {
                *end = 0;
            }
            end--;
        }
        return end;
    }

    const char *remove_leading_slash(const char *str) {
        while (*str == '/') {
            str++;
        }
        return str;
    }

    void copy_string(const char *str) {
        while (*str) {
            if (*str != 0) {
                if (*str == '/' && str[1] == '/') {
                    str++;
                    continue;
                }
            }
            *it_++ = *str++;
        }
        *it_ = 0;
    }

    void cat(const char *str) {
        copy_string(str);
        it_ = remove_trailing_slash(path_, it_);
    }

public:

    path()
            : path_(new char[initial_size_]) {
        it_ = path_;
        *it_ = 0;
    }

    ~path() {
        delete [] path_;
    }

    path(const path &p)
            : path_(new char[initial_size_]) {
        it_ = path_;
        cat(p.path_);
    }

    path &operator=(const path &p) {
        it_ = path_;
        cat(p.path_);
        return *this;
    }

    path(const char *str)
            : path_(new char[initial_size_]) {
        it_ = path_;
        cat(str);
    }

    void append(const char *str) {
        str = remove_leading_slash(str);
        *it_++ = '/';
        cat(str);
    }

    path operator/(const char *str) {
        path p(path_);
        p.append(str);
        return p;
    }

    path &operator/=(const path &p) {
        append(p.path_);
        return *this;
    }

    const char *get() const {
        return path_;
    }

    operator const char*() const {
        return path_;
    }

    bool operator==(const char *str) const {
        return strcmp(path_, str) == 0;
    }

    const char *basename() const {
        auto ptr = strrchr(path_, '/');
        if (ptr) {
            return ptr + 1;
        }
        return path_;
    }

};

} // namespace yacppl

