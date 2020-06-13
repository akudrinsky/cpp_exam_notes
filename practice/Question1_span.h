#ifndef UNTITLED1_SPAN_H
#define UNTITLED1_SPAN_H

#include <cstdio>
#include <exception>

template<typename TypeValue>
class span {
private:

    TypeValue *start = nullptr;
    size_t size = 0;

public:

    constexpr span ()                  noexcept            = default;

    // Rule of three
    constexpr span            (const span &other) noexcept = default;
    constexpr span &operator= (const span &other) noexcept = default;
             ~span            ()                  noexcept = default;

    // Constructors
    span (TypeValue *pointer, int new_size) :
            start (pointer),
            size (new_size) {
        if (new_size < 0)
            throw std::out_of_range ("size < 0");
    }

    template<size_t _size>
    constexpr span (TypeValue (&array)[_size]) noexcept:
            start (array),
            size (_size) { }

    // Index-th element of the sequence
    constexpr TypeValue &operator[] (int index) const { return *(start + index); }
    constexpr TypeValue &operator() (int index) const { return *(start + index); }

    // Basic methods
    constexpr TypeValue& front () const          {return *start;}
    constexpr TypeValue& back  () const          {return *(start + size);}
    constexpr TypeValue* data  () const noexcept { return start; }

    constexpr bool   empty      () const noexcept { return size == 0; }
    constexpr size_t size_      () const noexcept { return size; }
    constexpr size_t size_bytes () const noexcept { return size * sizeof (TypeValue); }


    // Obtains a span that is a view over the first/last Count elements of this span
    constexpr span<TypeValue> first (size_t new_size) const {
        if (new_size > size)
            throw std::out_of_range ("new_size > size");

        return span (start, new_size);
    }


    constexpr span<TypeValue> last (size_t new_size) const {
        if (new_size > size)
            throw std::out_of_range ("new_size > size");

        return span (start + size - new_size, new_size);
    }


    // Obtains a span that is a view over the Count elements of this span starting at offset Offset
    constexpr span<TypeValue> subspan(size_t offset, size_t new_size) const
    {
        if (offset + new_size > size)
            throw std::out_of_range("subspan wrong arguments");

        return span (start + offset, new_size);
    }

};


#endif //UNTITLED1_SPAN_H
