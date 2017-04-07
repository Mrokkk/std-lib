#pragma once

#include "string.h"
#include "algorithm.h"

namespace yacppl {

class path final {

public:

    class const_iterator {
        // TODO
    };

private:

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

    const char *omit_leading_slash(const char *str) {
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
        str = omit_leading_slash(str);
        *it_++ = '/';
        cat(str);
    }

    path operator/(const char *str) const {
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
        return compare(path_, str) == 0;
    }

    const char *basename() const {
        auto ptr = last_occurrence(path_, '/');
        if (ptr != end(path_)) {
            return ptr + 1;
        }
        return path_;
    }

};

} // namespace yacppl

