#pragma once

#include <cstring>

namespace yacppl {

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

public:

    path()
            : path_(new char[initial_size_]) {
        it_ = path_;
        *it_ = 0;
    }

    ~path() {
        if (path_)
            delete path_;
    }

    path(const path &p)
            : path_(new char[initial_size_]) {
        it_ = path_;
        append(p.path_);
    }

    path &operator=(const path &p) {
        it_ = path_;
        append(p.path_);
        return *this;
    }

    path(const char *str)
            : path_(new char[initial_size_]) {
        it_ = path_;
        append(str);
    }

    void append(const char *str) {
        *it_++ = '/';
        while (*str == '/') {
            str++;
        }
        while (*str) {
            if (*str == '/' && str[1] == '/') {
                str++;
                continue;
            }
            *it_++ = *str++;
        }
        *it_ = 0;
        it_ = remove_trailing_slash(path_, it_);
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

    operator const char*() const {
        return path_;
    }

    bool operator==(const char *str) const {
        return strcmp(path_, str) == 0;
    }

};

} // namespace yacppl

