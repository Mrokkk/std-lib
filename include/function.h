#pragma once

namespace yacppl {

template <typename Type>
class function {

    Type *function_ = nullptr;

public:

    constexpr function() = default;

    function(const Type *ptr) : function_(ptr) {
    }

    template <typename ...Types>
    auto operator()(Types &&... args) {
        return function_(args...);
    }

    operator bool() const {
        return function_ != nullptr;
    }

};

} // namespace yacppl

