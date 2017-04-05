#pragma once

namespace yacppl {

class path {

    // TODO: create string class
    char *path_;

public:

    path()
        : path_(new char[256]) {
    }

    path(const char *str)
            : path_(new char[256]) {
        // FIXME
        auto ptr = path_;
        while (*str) {
            *ptr = *str++;
        }
    }

    path &operator/(const char *) {
        return *this;
    }

    path &operator/(const path &) {
        return *this;
    }

    operator const char*() const {
        return path_;
    }

};

} // namespace yacppl

