#pragma once

#include <cstddef>
#include "iterator.hpp"

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

    void release() {
        if (string_) {
            delete [] string_;
        }
        string_ = nullptr;
        end_ = nullptr;
        size_ = 0;
        allocation_counter_ = 0;
    }

    void copy_from(const char *str) {
        if (str == nullptr) {
            release();
            return;
        }
        auto len = ::yacppl::length(str);
        if (string_) {
            if (len > length()) {
                reallocate(len);
            }
        }
        else {
            allocate(len);
        }
        copy(str, string_);
        end_ += len;
    }

    void move_from(string &s) {
        string_ = s.string_;
        end_ = s.end_;
        size_ = s.size_;
        allocation_counter_ = s.allocation_counter_;
        s.string_ = nullptr;
        s.end_ = nullptr;
        s.size_ = 0;
        s.allocation_counter_ = 0;
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

    string(string &&s) {
        move_from(s);
    }

    string &operator=(const char *str) {
        copy_from(str);
        return *this;
    }

    string &operator=(const string &s) {
        copy_from(s.string_);
        return *this;
    }

    string &operator=(string &&s) {
        release();
        move_from(s);
        return *this;
    }

    ~string() {
        release();
    }

    iterator begin() {
        return string_;
    }

    const_iterator begin() const {
        return string_;
    }

    const_iterator cbegin() const {
        return string_;
    }

    iterator end() {
        return end_;
    }

    const_iterator end() const {
        return end_;
    }

    const_iterator cend() const {
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

    string &append(char c) {
        char str[2] = {c, 0};
        append(str);
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

    void reserve(size_t size) {
        if (string_) {
            reallocate(size);
        }
        else {
            allocate(size);
        }
    }

};

} // namespace yacppl

