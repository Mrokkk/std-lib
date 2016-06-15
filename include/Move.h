//
// Created by maciek on 14.06.16.
//

#pragma once

template <typename Type>
inline Type &&move(Type &moved)
{
    return static_cast<Type &&>(moved);
}
