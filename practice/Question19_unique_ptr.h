#ifndef UNTITLED1_UNIQUE_PTR_H
#define UNTITLED1_UNIQUE_PTR_H

#include <iostream>
#include <memory>

template<typename TypeValue, typename Deleter = std::default_delete<TypeValue>>
class unique_ptr
{
private:
    TypeValue* pointer;
    Deleter    deleter;

public:

    unique_ptr ():
        pointer (nullptr)
    { }

    explicit unique_ptr (TypeValue* ptr):
        pointer (ptr)
    { }

    explicit unique_ptr (TypeValue* ptr, const Deleter& deleter):
            pointer (ptr),
            deleter (deleter)
    { }

    explicit unique_ptr (TypeValue* ptr, std::remove_reference_t<Deleter>&& deleter):
            pointer (std::move (ptr) ),
            deleter (std::move (deleter) )
    { }



    unique_ptr            (const unique_ptr& init) = delete;
    unique_ptr& operator= (const unique_ptr& init) = delete;

    unique_ptr            (unique_ptr&& init) noexcept:
        pointer (init.pointer)
    { init = nullptr; }

    unique_ptr& operator= (unique_ptr&& init) noexcept
    {
        pointer = init.pointer;
        init = nullptr;

        return *this;
    }

    ~unique_ptr ()
    {
        if (pointer != nullptr)
            deleter (pointer);
    }

    TypeValue* get       () const noexcept
    { return pointer; }

    TypeValue& operator* () const noexcept
    { return *get (); }

    TypeValue* operator->() const noexcept
    { return get ();  }

    TypeValue* release   ()       noexcept
    {
        TypeValue* ret = pointer;
        pointer        = nullptr;

        return ret;
    }

    void reset (TypeValue* new_pointer = nullptr) noexcept
    {
        std::swap (pointer, new_pointer);

        if (new_pointer != nullptr)
            deleter (new_pointer);
    }
};



#endif //UNTITLED1_UNIQUE_PTR_H
