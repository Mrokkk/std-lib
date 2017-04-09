#pragma once

#include "string.h"
#include "algorithm.h"

namespace yacppl {

class path final {

public:

    class const_iterator final {

        const char *iterator_ = nullptr;

    public:

        explicit const_iterator(const char *path) : iterator_(path) {
        }

        const_iterator(const const_iterator &it) : iterator_(it.iterator_) {
        }

        const_iterator(const_iterator &&it) : iterator_(it.iterator_) {
            it.iterator_= nullptr;
        }

        string operator*() const {
            return string(iterator_, first_occurrence(iterator_, '/') - iterator_);
        }

        const_iterator &operator++() {
            auto it = first_occurrence(iterator_, '/');
            if (*it == 0) {
                iterator_ = it;
            }
            else {
                iterator_ = it + 1;
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator ret_val(iterator_);
            this->operator++();
            return ret_val;
        }

        bool operator==(const const_iterator &it) const {
            return iterator_ == it.iterator_;
        }

        bool operator!=(const const_iterator &it) const {
            return iterator_ != it.iterator_;
        }

        const_iterator operator+(unsigned a) {
            auto it = iterator_;
            for (auto i = 0u; i < a; ++i) {
                it = first_occurrence(it, '/');
                if (*it == 0) {
                    return const_iterator(it);
                }
                else {
                    ++it;
                }
            }
            return const_iterator(it);
        }

        explicit operator bool() const {
            if (*iterator_) {
                return true;
            }
            return false;
        }

    };

    using iterator = const_iterator;

private:

    static const constexpr unsigned initial_size_ = 32;

    char *path_;
    char *it_;

    char *remove_trailing_slash(char *start, char *end) {
        --end;
        for (; end > start; --end) {
            if (*end != '/') {
                return end + 1;
            }
            else {
                *end = 0;
            }
        }
        return end + 1;
    }

    const char *omit_leading_slash(const char *str) {
        while (*str == '/') {
            str++;
        }
        return str;
    }

    void cat(const char *str) {
        it_ = copy(str, it_, [this](const char *c) {
            if (*c == '/' && c[1] == '/') {
                return false;
            }
            return true;
        });
        it_ = remove_trailing_slash(path_, it_);
    }

public:

    path() : path_(new char[initial_size_]) {
        it_ = path_;
        *it_ = 0;
    }

    ~path() {
        delete [] path_;
    }

    path(const path &p) : path_(new char[initial_size_]) {
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

    auto cbegin() const {
        if (*path_ == '/') {
            return const_iterator(path_ + 1);
        }
        else {
            return const_iterator(path_);
        }
    }

    auto begin() const {
        return cbegin();
    }

    auto cend() const {
        return const_iterator(it_);
    }

    auto end() const {
        return cend();
    }

    const char *basename() const {
        auto ptr = last_occurrence(path_, '/');
        if (ptr != ::yacppl::end(path_)) {
            return ptr + 1;
        }
        return path_;
    }

};

} // namespace yacppl

