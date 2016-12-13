#pragma once

#include "types.h"

namespace yacppl {

template <typename Type>
inline constexpr Type &&forward(typename remove_reference<Type>::type &t) {
    return static_cast<Type &&>(t);
}

template <typename Type>
inline constexpr Type &&forward(typename remove_reference<Type>::type &&t) {
    return static_cast<Type &&>(t);
}

template<typename Type>
inline typename remove_const<Type>::type &&move(Type &moved) {
    return static_cast<Type &&>(moved);
}

} // namespace yacppl

