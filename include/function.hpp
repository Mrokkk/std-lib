#pragma once

#include "move.hpp"
#include "types.hpp"
#include "unique_ptr.hpp"

namespace yacppl {

template <typename R, typename ...Args>
class callable {
public:
    virtual ~callable() {}
    virtual R operator()(Args ...args) = 0;
};

template<typename ClosureType, typename R, typename ...Args>
class closure: public callable<R, Args...> {

    const ClosureType func_;

public:

    closure(const ClosureType& handler) : func_(handler) {
    }

    ~closure() {
    }

    R operator()(Args ...args) override {
        if (is_void<R>::value)
            func_(forward<Args>(args)...);
        else
            return func_(forward<Args>(args)...);
    }

};

template <typename FunctionType>
class function : public function<decltype(&FunctionType::operator())> {
};

template <typename R, typename ...Args>
class function<R(Args...)> {

    unique_ptr<callable<R, Args...>> func_wrapper_;

public:

    function() = default;

    template<typename ClosureType>
    function(const ClosureType& function)
            : func_wrapper_(new closure<decltype(function), R, Args...>(function)) {
    }

    function &operator=(nullptr_t) = delete;

    template<typename ClosureType>
    function &operator=(const ClosureType& function) {
        func_wrapper_ = new closure<decltype(function), R, Args...>(function);
        return *this;
    }

    template <typename T = R>
    typename enable_if<is_void<T>::value, T>::type operator()(Args ...args) {
        (*func_wrapper_)(forward<Args>(args)...);
    }

    template <typename T = R>
    typename enable_if<!is_void<T>::value, T>::type operator()(Args ...args) {
        return (*func_wrapper_)(forward<Args>(args)...);
    }

    operator bool() const {
        return func_wrapper_ != nullptr;
    }

};

} // namespace yacppl

