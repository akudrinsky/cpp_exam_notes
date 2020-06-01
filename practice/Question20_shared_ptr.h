#ifndef UNTITLED1_SHARED_PTR_H
#define UNTITLED1_SHARED_PTR_H


#include <cstdlib>
#include <iostream>

template<typename TypeValue>
class shared_ptr
{

private:
    TypeValue* pointer;
    long*    counter;

public:

    constexpr shared_ptr ():
        pointer (nullptr),
        counter (new long(1))
    { }

    explicit shared_ptr (TypeValue* pointer):
        pointer (pointer),
        counter (new long(1))
    { }

    shared_ptr (const shared_ptr& init):
        pointer (init.pointer),
        counter (init.counter)
    { (*counter)++; }

    shared_ptr& operator= (const shared_ptr& init)
    {
        pointer = init.pointer;
        counter = init.counter;

        (*counter)++;
    }


    shared_ptr (shared_ptr&& init) noexcept:
        pointer (init.pointer),
        counter (init.counter)
    { init.pointer = init.counter = nullptr; }

    void destruct ()
    {
        if (counter != nullptr)
        {
            (*counter)--;

            if (*counter == 0)
            {
                delete pointer;
                delete counter;
            }
        }
    }

    shared_ptr& operator= (shared_ptr&& init) noexcept
    {
        destruct ();

        pointer      = init.pointer;
        counter      = init.counter;
        init.pointer = init.counter = nullptr;

        return *this;
    }

    ~shared_ptr ()
    { destruct (); }

    void swap (shared_ptr& other)
    {
        std::swap (pointer, other.pointer);
        std::swap (counter, other.counter);
    }

    void reset () noexcept
    { shared_ptr().swap (*this);     }

    void reset (shared_ptr other)
    { shared_ptr(other).swap (*this); }



    TypeValue* get       () const noexcept
    { return pointer;  }

    TypeValue& operator* () const noexcept
    { return *get ();  }

    TypeValue* operator->() const noexcept
    { return get ();   }

    long use_count ()     const noexcept
    { return *counter; }
};


#endif //UNTITLED1_SHARED_PTR_H
