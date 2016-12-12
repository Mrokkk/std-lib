#pragma once

namespace yacppl {

template <class T>
struct remove_const {
    typedef T type;
};

template <class T>
struct remove_const<const T> {
    typedef T type;
};

} // namespace yacppl

