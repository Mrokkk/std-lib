#pragma once

namespace yacppl {

template<typename Type>
inline Type &&move(Type &moved) {
    return static_cast<Type &&>(moved);
}

} // namespace yacppl
