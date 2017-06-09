#pragma once

#include "string.hpp"
#include "algorithm.hpp"

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
            if (*iterator_ == '/') {
                return string("/");
            }
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

    string path_;

    char *find_trailing_slash(char *begin, char *end) {
        --end;
        for (; end > begin; --end) {
            if (*end != '/') {
                return end + 1;
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
        for (auto it = str; it != ::yacppl::cend(str); ++it) {
            if (*it == '/' && it[1] == '/') {
            }
            else {
                path_.append(*it);
            }
        }
        path_.erase(find_trailing_slash(path_.begin(), path_.end()), path_.end());
    }

public:

    path() = default;

    path(const path &p) {
        path_ = p.path_;
    }

    path(path &&p) {
        path_ = p;
        p.path_ = nullptr;
    }

    path(const char *str) {
        if (str == nullptr) {
            return;
        }
        cat(str);
    }

    path &operator=(const path &p) {
        path_ = p.path_;
        return *this;
    }

    path &operator=(path &&p) {
        path_ = p.path_;
        return *this;
    }

    void append(const char *str) {
        auto len = length(str);
        if (len) {
            path_.append('/');
        }
        str = omit_leading_slash(str);
        cat(str);
    }

    path operator/(const char *str) const {
        path p;
        if (not path_.empty()) {
            p = *this;
        }
        p.append(str);
        return p;
    }

    path &operator/=(const path &p) {
        append(p.path_);
        return *this;
    }

    const char *get() const {
        return static_cast<const char *>(path_);
    }

    operator const char*() const {
        return path_;
    }

    bool operator==(const char *str) const {
        return path_ == str;
    }

    auto cbegin() const {
        return const_iterator(path_.cbegin());
    }

    auto begin() const {
        return cbegin();
    }

    auto cend() const {
        return const_iterator(path_.cend());
    }

    auto end() const {
        return cend();
    }

    string basename() const {
        auto ptr = last_occurrence(path_, '/');
        if (ptr != ::yacppl::end(path_)) {
            return ptr + 1;
        }
        return path_;
    }

    string dirname() const {
        auto ptr = last_occurrence(path_, '/');
        if (ptr == ::yacppl::cend(path_)) {
            return string("");
        }
        if (ptr == path_) {
            return string(path_, ptr - path_ + 1);
        }
        return string(path_, ptr - path_);
    }

};

} // namespace yacppl

