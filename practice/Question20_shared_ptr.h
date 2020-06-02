#ifndef UNTITLED1_SHARED_PTR_H
#define UNTITLED1_SHARED_PTR_H


#include <cstdlib>
#include <iostream>
#include <utility>

template<typename TypeValue>
class shared_ptr;

#pragma pack (push, 1)
template<typename TypeValue>
class shared_ptr_base
{
protected:
    int*       counter;
    TypeValue* pointer;
    bool       init_type = false;
public:

    shared_ptr_base ():
        pointer (nullptr),
        counter (new int(1))
    { }


    shared_ptr_base (TypeValue* pointer, int* counter):
        pointer   (pointer),
        counter   (counter),
        init_type (true)
    { (*counter) = 1; }

    explicit shared_ptr_base (TypeValue* pointer):
        pointer (pointer),
        counter (new int(1))
    { }

    shared_ptr_base (const shared_ptr_base& init):
            pointer (init.pointer),
            counter (init.counter)
    { (*counter)++; }

    shared_ptr_base& operator= (const shared_ptr_base& init)
    {
        pointer = init.pointer;
        counter = init.counter;

        (*counter)++;
    }


    shared_ptr_base (shared_ptr_base&& init) noexcept:
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

                if (init_type == false)
                {
                    delete pointer;
                    delete counter;
                }
                else
                {
                    delete [] reinterpret_cast<char*> (counter);
                }

            }
        }
    }

    shared_ptr_base& operator= (shared_ptr_base&& init) noexcept
    {
        destruct ();

        pointer      = init.pointer;
        counter      = init.counter;
        init.pointer = init.counter = nullptr;

        return *this;
    }

    ~shared_ptr_base ()
    { destruct (); }

    void reset () noexcept
    { shared_ptr_base().swap (*this);}

    TypeValue* get       () const noexcept
    { return pointer;  }

    TypeValue& operator* () const noexcept
    { return *get ();  }

    TypeValue* operator->() const noexcept
    { return get ();   }

    int use_count ()     const noexcept
    { return *counter; }



};
#pragma pack (pop)

template<typename TypeValue>
class shared_ptr: public shared_ptr_base<TypeValue>
{

    template<typename Type, typename... Args>
    friend shared_ptr<Type> make_shared (Args&&... args);

private:

    shared_ptr (TypeValue* pointer, int* counter):
            shared_ptr_base<TypeValue> (pointer, counter)
    { }

public:
    explicit shared_ptr (TypeValue* pointer):
        shared_ptr_base<TypeValue> (pointer)
    { }

    void swap (shared_ptr& other)
    {
        std::swap (this->pointer, other.pointer);
        std::swap (this->counter, other.counter);
    }

    template<typename Other>
    void reset (Other* other)
    { shared_ptr(other).swap (*this); }



};

template<typename TypeValue, typename... Args>
shared_ptr<TypeValue> make_shared (Args&&... args)
{
    char* emplace = new char[sizeof (int) + sizeof (TypeValue)];
    new (emplace + sizeof (int)) TypeValue (std::forward<Args> (args)...);

    return shared_ptr<TypeValue> (reinterpret_cast<TypeValue*> (emplace + sizeof (int)), reinterpret_cast<int*> (emplace) );
}


#endif //UNTITLED1_SHARED_PTR_H
