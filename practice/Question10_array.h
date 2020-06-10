#ifndef Q10_ARRAY_H_
#define Q10_ARRAY_H_

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#include <cstddef>
#include <exception>
#include <type_traits>

// TODO encapsulate array itself and allow for empty container to be created

template <typename _Tp, std::size_t _Nm>
struct __array_traits {
    typedef _Tp _Type[_Nm];  // Now _Type is an array

    static constexpr _Tp &getReference(const _Type &t, std::size_t n) noexcept {
        return const_cast<_Tp &>(t[n]);
    }

    static constexpr _Tp *getPointer(const _Type *t) noexcept {
        return const_cast<_Tp *>(t);
    }
};

template <typename _Tp>
struct __array_traits<_Tp, 0> {
    struct _Type {};  // Stub for empty array

    static constexpr _Tp &getReference(const _Type &, std::size) noexcept {
        return *const_cast<_Tp &>(nullptr);
    }

    static constexpr _Tp *getPointer(const _Type &) noexcept {
        return nullptr;
    }
};

template <typename _Tp, std::size_t _Nm>
class array {
    // Some handy aliases
    typedef _Tp value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef __array_traits<_Tp, _Nm>::_Type array_type;

    array_type arr; // Array itself

    // Constructor, destructor and operator= are implicitly declared for
    // std::array

    // Note that since array is allocated on the stack, it is possible to do many
    // calculations in compile time

    // Element access methods
    constexpr reference at(size_type pos) {
        // Since C++17 at() should be implemented as constexpr
        if (pos < size()) {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr const_reference at(size_type pos) const {
        // Constant version of at()
        if (pos < size()) {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr reference operator[](size_type pos) {
        // Since C++17 operator[] should be constexpr
        return __array_traits::getReference(arr, pos);
    }

    constexpr const_reference operator[](size_type pos) const {
        // Constant version of operator[]
        return __array_traits::getReference(arr, pos);
    }

    // Note that calling front() and back() on an empty container is considered UB

    constexpr reference front() {
        // Access the first element
        return __array_traits::getReference(arr, 0);
    }

    constexpr const_reference front() const {
        // Constant version of front()
        return __array_traits::getReference(arr, 0);
    }

    constexpr reference back() {
        // Access the last element
        return __array_traits::getReference(arr, _Nm - 1);
    }

    constexpr const_reference back() const {
        // Constant version of back()
        return __array_traits::getReference(arr, _Nm - 1);
    }

    constexpr pointer data() noexcept {
        // Direct access to underlying array
        return __array_traits::getPointer(arr);
    }

    constexpr const_pointer data() const noexcept {
        // Const version of data()
        return __array_traits::getPointer(arr);
    }

    // Capacity methods
    constexpr bool empty() const noexcept {
        // Check whether an array is empty. NOTE: Since C++20 [[nodiscard]] is required
        return _Nm ? 0 : 1;
    }

    constexpr size_type size() const noexcept {
        // Get size of container
        return _Nm;
    }

    constexpr size_type max_size() const noexcept {
        // Get maximal size of container
        return _Nm;
    }

    // Operations
    void fill(const_reference value) {
        // Fill an array. Since C++20 should be constexpr.
        for (int i = 0; i < _Nm; i++) {
            __array_traits::getReference(arr, i) = value;  // Everything is nice since it
        }
    }

    void swap(array &other) noexcept(std::is_nothrow_swappable(value_type)) {
        // Requires custom swap specification
        for (int i = 0; i < _Nm; i++) {
            std::swap(__array_traits::getReference(arr, i), __array_traits::getReference(other.arr, i));
            // Just swap elementwise, I guess (solution in GCC implementation relies on iterators)
        }
    }
};

#endif  // Q10_ARRAY_H_
