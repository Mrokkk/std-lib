#pragma once

#include "types.h"

namespace yacppl {

template<typename Type>
inline typename remove_const<Type>::type &&move(Type &moved) {
    return static_cast<Type &&>(moved);
}

} // namespace yacppl

