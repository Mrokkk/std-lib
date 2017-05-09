#pragma once

#include "types.hpp"

namespace yacppl {

template <typename Type>
class function {

    Type *function_ = nullptr;

public:

    function() = default;

    template <typename Lambda>
    function(Lambda ptr) : function_(ptr) {
    }

    template <typename Lambda>
    function &operator=(Lambda lambda) {
        function_ = lambda;
        return *this;
    }

    template <typename ...Types>
    auto operator()(Types &&... args) const {
        return function_(args...);
    }

    operator bool() const {
        return function_ != nullptr;
    }

};

template <typename R, typename ...Args>
function<R(Args...)> make_function(R (*f)(Args...)) {
    return function<R(Args...)>(f);
}

} // namespace yacppl

