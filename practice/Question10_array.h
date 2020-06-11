#ifndef Q10_ARRAY_H_
#define Q10_ARRAY_H_

#include <cstddef>
#include <exception>
#include <stdexcept>
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

    static constexpr _Tp &getReference(const _Type &, std::size_t) noexcept {
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

    typedef typename __array_traits<_Tp, _Nm>::_Type array_type;

    array_type arr;  // Array itself

    // Constructor, destructor and operator= are implicitly declared for
    // std::array

    // Note that since array is allocated on the stack, it is possible to do many
    // calculations in compile time
   public:
    // Element access methods
    constexpr reference at(size_type pos) {
        // Since C++17 at() should be implemented as constexpr
        if (pos >= size()) {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr const_reference at(size_type pos) const {
        // Constant version of at()
        if (pos >= size()) {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr reference operator[](size_type pos) {
        // Since C++17 operator[] should be constexpr
        return __array_traits<_Tp, _Nm>::getReference(arr, pos);
    }

    constexpr const_reference operator[](size_type pos) const {
        // Constant version of operator[]
        return __array_traits<_Tp, _Nm>::getReference(arr, pos);
    }

    // Note that calling front() and back() on an empty container is considered UB

    constexpr reference front() {
        // Access the first element
        return __array_traits<_Tp, _Nm>::getReference(arr, 0);
    }

    constexpr const_reference front() const {
        // Constant version of front()
        return __array_traits<_Tp, _Nm>::getReference(arr, 0);
    }

    constexpr reference back() {
        // Access the last element
        return __array_traits<_Tp, _Nm>::getReference(arr, _Nm - 1);
    }

    constexpr const_reference back() const {
        // Constant version of back()
        return __array_traits<_Tp, _Nm>::getReference(arr, _Nm - 1);
    }

    constexpr pointer data() noexcept {
        // Direct access to underlying array
        return __array_traits<_Tp, _Nm>::getPointer(arr);
    }

    constexpr const_pointer data() const noexcept {
        // Const version of data()
        return __array_traits<_Tp, _Nm>::getPointer(arr);
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
        for (size_type i = 0; i < _Nm; i++) {
            __array_traits<_Tp, _Nm>::getReference(arr, i) = value;  // Everything is nice since all values are initialized
        }
    }

    void swap(array &other) noexcept(std::is_nothrow_swappable<value_type>()) {
        // Requires custom swap specification
        for (size_type i = 0; i < _Nm; i++) {
            std::swap(__array_traits<_Tp, _Nm>::getReference(arr, i), __array_traits<_Tp, _Nm>::getReference(other.arr, i));
            // Just swap elementwise, I guess (solution in GCC implementation relies on iterators)
        }
    }
};

// Some unit testing to ensure that everything works fine

void question10_test() {
    array<int, 0> empty_arr;  // Empty array
    if (!empty_arr.empty()) {
        throw std::runtime_error("At Question10: Empty array is considered non-empty");
    }

    if (empty_arr.data() != nullptr) {
        throw std::runtime_error("At Question10: Non-nullptr pointer to empty array");
    }

    array<int, 10> arr1;
    arr1.fill(44);

    if (arr1.size() != 10)
        throw std::runtime_error("At Question10: Invalid size");

    if (arr1.max_size() != 10)
        throw std::runtime_error("At Question10: Invalid max_size");

    for (int i = 0; i < 10; i++) {
        if (arr1[i] != 44 || arr1.at(i) != 44)
            throw std::runtime_error("At Question10: Fill does not fill the whole array or access function works improperly");
    }

    bool flag = false;

    try {
        arr1.at(11);
    } catch (const std::exception &e) {
        flag = true;
    }

    if (!flag)
        throw std::runtime_error("At Question10: at() did not detected array overflow");

    array<int, 10> arr2;

    for (int i = 0; i < 10; i += 2) {
        arr2[i] = i;
        arr2.at(i + 1) = i + 1;
    }

    for (int i = 0; i < 10; i++) {
        if (arr2[i] != i || arr2.at(i) != i)
            throw std::runtime_error("At Question10: Either at or operator[] are working improperly");
    }

    arr1.swap(arr2);

    for (int i = 0; i < 10; i++) {
        if (arr1[i] != i || arr1.at(i) != i)
            throw std::runtime_error("At Question10: Swap works improperly");
    }

    if(arr1.front() != 0) {
        throw std::runtime_error("At Question10: Front works improperly");
    }

    if(arr1.back() != 9) {
        throw std::runtime_error("At Question10: Back works improperly");
    }
}

#endif  // Q10_ARRAY_H_
