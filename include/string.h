#pragma once

#include <cstddef>
#include "iterator.h"

namespace yacppl {

inline auto memcopy(const char *s, char *d, size_t size) {
    while (size--) {
        *d++ = *s++;
    }
    return d;
}

inline auto copy(const char *s1, char *s2) {
    while (*s1) {
        *s2++ = *s1++;
    }
    *s2 = 0;
    return s2;
}

template <typename F>
inline auto copy(const char *s1, char *s2, F callback) {
    while (*s1) {
        if (callback(s1)) {
            *s2++ = *s1++;
        }
        else {
            ++s1;
        }
    }
    *s2 = 0;
    return s2;
}

inline auto copy(const char *s1, char *s2, size_t n) {
    s2 = memcopy(s1, s2, n);
    *s2 = 0;
    return s2;
}

inline int compare(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

class string final {

    char *string_ = nullptr;
    char *end_ = nullptr;
    size_t size_ = 0;
    size_t allocation_counter_ = 0;

    void allocate(size_t size) {
        string_ = new char[size + 1];
        end_ = string_;
        allocation_counter_++;
        size_ = size;
    }

    void reallocate(size_t size) {
        auto new_string = new char[size + 1];
        copy(string_, new_string);
        delete [] string_;
        string_ = new_string;
        size_ = size;
        end_ = string_ + ::yacppl::length(string_);
        allocation_counter_++;
    }

public:

    using iterator = char *;
    using const_iterator = const char *;

    string() = default;

    string(const char *str) {
        auto len = ::yacppl::length(str);
        allocate(len);
        copy(str, string_);
        end_ += len;
    }

    string(const string &s) {
        auto len = s.length();
        allocate(len);
        copy(s.string_, string_);
        end_ += len;
    }

    string(const char *begin, size_t size) {
        allocate(size);
        copy(begin, string_, size);
        end_ += size;
    }

    ~string() {
        if (string_) {
            delete [] string_;
        }
    }

    auto cbegin() const {
        return string_;
    }

    auto begin() {
        return string_;
    }

    auto cend() const {
        return end_;
    }

    auto end() const {
        return end_;
    }

    bool operator==(const char *str) const {
        if (string_ == nullptr) {
            if (str[0] == 0) return true;
            return false;
        }
        return compare(str, string_) == 0;
    }

    operator const char *() const {
        return string_;
    }

    string &append(const char *str) {
        auto len = ::yacppl::length(str);
        size_t current_len = end_ - string_;
        if (current_len + len >= size_) {
            if (string_) {
                reallocate(current_len + len + size_);
            }
            else {
                allocate(current_len + len + size_);
            }
        }
        copy(str, end_);
        end_ += len;
        return *this;
    }

    string substring(size_t pos, size_t len) const {
        auto new_begin = string_ + pos;
        if (len > reinterpret_cast<size_t>(end_) - reinterpret_cast<size_t>(new_begin)) {
            len = end_ - new_begin;
        }
        return string(string_ + pos, len);
    }

    void erase(iterator begin, const_iterator end) {
        if (begin > end) {
            return;
        }
        ::yacppl::memcopy(end, begin, end_ - end);
        end_ -= end - begin;
        *end_ = 0;
    }

    size_t length() const {
        return end_ - string_;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return length() == 0;
    }

};

} // namespace yacppl

