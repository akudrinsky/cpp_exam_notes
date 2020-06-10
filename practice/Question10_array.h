#ifndef Q10_ARRAY_H_
#define Q10_ARRAY_H_

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#include <cstddef>
#include <type_traits>
#include <exception>

// TODO encapsulate array itself and allow for empty container to be created

template <typename _Tp, std::size_t _Nm>
class array
{
    typedef _Tp value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    value_type arr[_Nm]; // Array itself

    // Note that since array is allocated on the stack, it is possible to do many calculations in compile time

    // Element access methods
    constexpr reference at(size_type pos)
    {
        ; // Since C++17 at() should be implemented as constexpr
        if (pos < size())
        {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr const_reference at(size_type pos) const
    { // Constant version of at()
        if (pos < size())
        {
            throw std::runtime_error("Address overflow in array::at() function");
        }

        return operator[](pos);
    }

    constexpr reference operator[](size_type pos)
    { // Since C++17 operator[] should be constexpr
        return arr[pos];
    }

    constexpr const_reference operator[](size_type pos) const
    { // Constant version of operator[]
        return arr[pos];
    }

    // Note that calling front() and back() on an empty container is considered UB

    constexpr reference front()
    { // Access the first element
        return arr[0];
    }

    constexpr const_reference front() const
    { // Constant version of front()
        return arr[0];
    }

    constexpr reference back()
    { // Access the last element
        return arr[_Nm - 1];
    }

    constexpr const_reference back() const
    { // Constant version of back()
        return arr[_Nm - 1];
    }

    constexpr pointer data() noexcept
    { // Direct access to underlying array
        return arr;
    }

    constexpr const_pointer data() const noexcept
    { // Const version of data()
        return arr;
    }

    // Capacity methods
    constexpr bool empty() const noexcept
    { // Check whether an array is empty. NOTE: Since C++20 [[nodiscard]] is required
        return _Nm ? 0 : 1;
    }
    
    constexpr size_type size() const noexcept
    { // Get size of container
        return _Nm;
    }
    
    constexpr size_type max_size() const noexcept
    { // Get maximal size of container
        return _Nm;
    }
    
    // Operations
    void fill(const_reference value);                                        // Fill an array. Since C++20 should be constexpr.
    void swap(array &other) noexcept(std::is_nothrow_swappable(value_type)); // Requires custom swap specification
};

#endif // Q10_ARRAY_H_
