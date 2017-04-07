#pragma once

#include "string.h"
#include "algorithm.h"

//FIXME in test: path.paths_are_normalized
//==14533== Invalid read of size 1
//==14533==    at 0x447279: yacppl::path::remove_trailing_slash(char*, char*) (path.h:42)
//==14533==    by 0x44737A: yacppl::path::cat(char const*) (path.h:75)
//==14533==    by 0x447473: yacppl::path::path(char const*) (path.h:105)
//==14533==    by 0x4474F5: yacppl::path::operator/(char const*) const (path.h:115)
//==14533==    by 0x44654C: path_paths_are_normalized() (path.cpp:35)
//==14533==    by 0x421BBB: yatf::detail::test_session::test_case::test_case(char const*, char const*, void (*)())::{lambda(void (*)())#1}::operator()(void (*)()) const (yatf.h:190)
//==14533==    by 0x421BDB: yatf::detail::test_session::test_case::test_case(char const*, char const*, void (*)())::{lambda(void (*)())#1}::_FUN(void (*)()) (yatf.h:190)
//==14533==    by 0x41F99A: yatf::detail::test_session::test_case::call() (yatf.h:216)
//==14533==    by 0x41FD49: yatf::detail::test_session::run(yatf::config) (yatf.h:291)
//==14533==    by 0x41FFA5: yatf::main(int (*)(char const*, ...), unsigned int, char const**) (yatf.h:395)
//==14533==    by 0x41F857: main (main.cpp:6)
//==14533==  Address 0x5aff49f is 1 bytes before a block of size 256 alloc'd
//==14533==    at 0x4C2BCAF: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
//==14533==    by 0x447447: yacppl::path::path(char const*) (path.h:103)
//==14533==    by 0x4474F5: yacppl::path::operator/(char const*) const (path.h:115)
//==14533==    by 0x44654C: path_paths_are_normalized() (path.cpp:35)
//==14533==    by 0x421BBB: yatf::detail::test_session::test_case::test_case(char const*, char const*, void (*)())::{lambda(void (*)())#1}::operator()(void (*)()) const (yatf.h:190)
//==14533==    by 0x421BDB: yatf::detail::test_session::test_case::test_case(char const*, char const*, void (*)())::{lambda(void (*)())#1}::_FUN(void (*)()) (yatf.h:190)
//==14533==    by 0x41F99A: yatf::detail::test_session::test_case::call() (yatf.h:216)
//==14533==    by 0x41FD49: yatf::detail::test_session::run(yatf::config) (yatf.h:291)
//==14533==    by 0x41FFA5: yatf::main(int (*)(char const*, ...), unsigned int, char const**) (yatf.h:395)
//==14533==    by 0x41F857: main (main.cpp:6)

namespace yacppl {

class path final {

public:

    class const_iterator {

        const char *iterator_ = nullptr;

    public:

        const_iterator(const char *path) : iterator_(path) {
        }

        string operator*() {
            return string(iterator_, first_occurrence(iterator_, '/') - iterator_);
        }

        const_iterator &operator++() {
            iterator_ = first_occurrence(iterator_, '/') + 1;
            return *this;
        }

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

    auto cbegin() const {
        if (*path_ == '/') {
            return const_iterator(path_ + 1);
        }
        else {
            return const_iterator(path_);
        }
    }

};

} // namespace yacppl

