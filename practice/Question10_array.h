#ifndef Q10_ARRAY_H_
#define Q10_ARRAY_H_

#include <cstddef>
#include <type_traits>

template<typename _Tp, std::size_t _Nm>
class array {
    typedef _Tp                 value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef std::size_t         size_type;
    typedef std::ptrdiff_t      difference_type;

    value_type[sz];      // Array itself


    // Note that since array is allocated on the stack, it is possible to do many calculations in compile time


    // Element access methods
    constexpr reference at(size_type pos); // Since C++17 at() should be implemented as constexpr
    constexpr const_reference at(size_type pos) const; // Constant version of at()
    constexpr reference operator[](size_type pos); // Since C++17 operator[] should be constexpr
    constexpr const_reference operator[](size_type pos) const; // Constant version of operator[]
    constexpr reference front(); // Access the first element
    constexpr const_reference front() const; // Constant version of front()
    constexpr reference back(); // Access the last element
    constexpr const_reference back() const; // Constant version of back()
    constexpr pointer data() noexcept; // Direct access to underlying array
    constexpr const_pointer data() const noexcept; // Const version of data() 

    // Capacity methods
    constexpr bool empty() const noexcept; // Check whether an array is empty. NOTE: Since C++20 [[nodiscard]] is required
    constexpr size_type size() const noexcept; // Get size of container
    constexpr size_type max_size const noexcept; // Get maximal size of container

    // Operations
    void fill(const_reference value); // Fill an array. Since C++20 should be constexpr.
    void swap(array &other) noexcept(std::is_nothrow_swappable(value_type)); // Requires custom swap specification
};



#endif // Q10_ARRAY_H_
