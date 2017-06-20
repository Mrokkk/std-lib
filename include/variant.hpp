#pragma once

namespace yacppl {

namespace detail {

template <typename T>
struct type {

    constexpr explicit type() = default;

    constexpr explicit type(const T &val, char *data) : ptr_(new(data) T(val)) {
    }

    void visit() const {
    }

    void set(const T &val, char *data) {
        release();
        ptr_ = new(data) T(val);
    }

    void reset() {
        release();
    }

    operator bool() const {
        return ptr_ != nullptr;
    }

    ~type() {
        release();
    }

private:

    void release() {
        if (ptr_ != nullptr) {
            ptr_->~T();
            ptr_ = nullptr;
        }
    }

    T *ptr_ = nullptr;

};

template <typename ...Types>
struct max_sizeof {
};

template <typename T>
struct max_sizeof<T> {
    static constexpr const auto value = sizeof(T);
};

template <typename T1, typename T2>
struct max_sizeof<T1, T2> {
    static constexpr const auto value = sizeof(T1) > sizeof(T2) ? sizeof(T1) : sizeof(T2);
};

template <typename T1, typename T2, typename ...Rest>
struct max_sizeof<T1, T2, Rest...> {
    static constexpr const auto value = max_sizeof<T1, T2>::value > max_sizeof<Rest...>::value ?
        max_sizeof<T1, T2>::value : max_sizeof<Rest...>::value;
};

} // namespace detail

template <typename ...Types>
struct variant : detail::type<Types>... {

    constexpr variant() : data_() {
    }

    template <typename T>
    constexpr explicit variant(const T &v) : detail::type<T>(v, data_) {
    }

    template <typename T>
    void set(const T &value) {
        int list[] = {(detail::type<Types>::reset(), 0)...};
        (void)list;
        detail::type<T>::set(value, data_);
    }

    template <typename T>
    T &get() {
        detail::type<T>::visit();
        return *reinterpret_cast<T *>(data_);
    }

    template <typename T>
    const T &get() const {
        detail::type<T>::visit();
        return *reinterpret_cast<const T *>(data_);
    }

    template <typename T>
    T *safe_get() {
        if (detail::type<T>::operator bool()) {
            return reinterpret_cast<T *>(data_);
        }
        return nullptr;
    }

    template <typename T>
    const T *safe_get() const {
        if (detail::type<T>::operator bool()) {
            return reinterpret_cast<const T *>(data_);
        }
        return nullptr;
    }

    template <typename T>
    variant &operator=(const T &val) {
        set<T>(val);
        return *this;
    }

private:

    char data_[detail::max_sizeof<Types...>::value];

};

} // namespace yacppl

