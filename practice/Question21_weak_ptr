#ifndef UNTITLED1_WEAK_PTR_H
#define UNTITLED1_WEAK_PTR_H

#include "shared_ptr.h"

struct Counter
{
    int* shared_counter;
    int* weak_counter;

    Counter () = delete;

    Counter (int shared_counter, int weak_counter):
        shared_counter (new int (shared_counter) ),
        weak_counter   (new int (weak_counter) )
    { }

    ~Counter ()
    {
        delete shared_counter;
        delete weak_counter;
    }
};

template<typename TypeValue>
class weak_ptr
{
private:
    TypeValue* pointer;
    Counter*   counter;

public:

    void destruct ()
    {
        if (counter->shared_counter == 0 && counter->weak_counter == 0)
        {
            delete Counter;
        }
        else
        {
            counter->weak_counter--;
        }
    }

    // КУча неинтересных конструкторов

    constexpr weak_ptr () noexcept:
        pointer (nullptr),
        counter (new Counter(0, 1) )
    { }

    weak_ptr (const weak_ptr& init):
            pointer (init.pointer),
            counter (init.counter)
    { counter->weak_counter++; }

    weak_ptr (weak_ptr&& init):
            pointer (init.pointer),
            counter (init.counter)
    { }

    weak_ptr (const shared_ptr<TypeValue>& init):
        pointer (init.pointer),
        counter (init.counter)
    { counter->weak_counter++; }

    weak_ptr& operator= (const weak_ptr& init)
    {
        destruct ();

        pointer = init.pointer;
        counter = init.counter;

        counter->weak_counter++;
    }

    weak_ptr& operator= (weak_ptr&& init)
    {
        destruct ();

        pointer = init.pointer;
        counter = init.counter;
    }

    weak_ptr& operator= (const shared_ptr<TypeValue>& init)
    {
        destruct ();

        pointer = init.pointer;
        counter = init.counter;

        counter->weak_counter++;
    }

    ~weak_ptr ()
    { destruct (); }

    void reset () noexcept
    { destruct (); }

    void swap(weak_ptr& init) noexcept
    {
        std::swap (pointer, init.pointer);
        srd::swap (counter, init.counter);
    }

    int use_count () const noexcept
    { return counter->shared_counter; }

    bool expired () const noexcept
    { return  counter->shared_counter == 0; }

    shared_ptr<TypeValue> lock () const noexcept
    { return expired () ? shared_ptr () : shared_ptr (counter, pointer); }

};




#endif //UNTITLED1_WEAK_PTR_H
