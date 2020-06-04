#ifndef MY_VEC
#define MY_VEC


#include <stdexcept>
#include <utility>




template<typename TypeValue, typename Allocator = std::allocator<TypeValue>>
class vector
{
private:

    TypeValue* start;
    TypeValue* end;
    TypeValue* storage;
    Allocator  allocator;

public:

    vector (const Allocator& alloc = Allocator() ):
            start     (std::allocator_traits<Allocator>::allocate (allocator, 8) ),
            end       (start + 1),
            storage   (start + 8),
            allocator (alloc)
    { };

    // Rule of five

    // Rule of three
    vector (const vector& init):                                // Copy constructor
            start     (std::allocator_traits<Allocator>::allocate (allocator, init.storage - init.start)),  // Аллоцирует (init.storage - init.start) * sizeof(TypeValue) байт памяти
            end       (start + (init.end - init.start) ),
            storage   (start + (init.storage - init.start)),
            allocator (std::allocator_traits<Allocator>::select_on_container_copy_construction (init.allocator))
    // Copy constructors of AllocatorAwareContainers obtain their instances of the allocator
    // by calling std::allocator_traits<allocator_type>::select_on_container_copy_construction on the allocator of the container being copied.
    {
        for (size_t i = 0; i < init.end - init.start; i++)
        {
            // Конструирует объекты типа TypeValue на выделенной памяти
            std::allocator_traits<Allocator>::construct (allocator, start + i, *(init.start + i));
        }
    }

    vector& operator= (const vector& init)                      // Copy assignment operator
    {
        if (this != &init)
        {
            return *this;
        }

        for (size_t i = 0; i < end - start; i++)
        {
            // Деконструирует объекты типа NypeValue на занятой памяти, вызывая allocator.destroy,
            // если не получается, то (start + i)->~TypeValue
            std::allocator_traits<Allocator>::destroy (allocator, start + i);
        }

        // Copy-assignment will replace the allocator only
        // if std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value is true
        bool allocator_copy_required = std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value;


        // Аллокаторы равны, если один может деаллоцировать память, выделенную другим
        bool realloc_required = (allocator != init.allocator && allocator_copy_required) || storage - start < init.storage - init.start;

        if (realloc_required)
        {
            // Deallocate memory
            std::allocator_traits<Allocator>::deallocate (allocator, start, storage - start);
        }

        if (allocator_copy_required)
        {
            // Copy allocator
            allocator = init.allocator;
        }

        if (realloc_required)
        {
            // Allocate memory
            start   = std::allocator_traits<Allocator>::allocate (allocator, init.end - init.start);
            storage = start + (init.end - init.start);
        }

        end = start + (init.end - init.start);



        for (size_t i = 0; i < init.end - init.start; i++)
        {
            // Конструирует объекты типа TypeValue на выделенной памяти
            std::allocator_traits<Allocator>::construct (allocator, start + i, *(init.start + i));
        }

        return *this;
    }

    void destruct ()
    {
        for (size_t i = 0; i < end - start; i++)
        {
            // Деконструирует объекты типа NypeValue на занятой памяти, вызывая allocator.destroy,
            // если не получается, то (start + i)->~TypeValue
            std::allocator_traits<Allocator>::destroy (allocator, start + i);
        }

        std::allocator_traits<Allocator>::deallocate (allocator, start, storage - start);
    }

    ~vector () { destruct (); }                                 // Destructor
    //

    vector (vector&& init):                                     // Move constructor
            start     (init.start),
            end       (init.end),
            storage   (init.storage),
            allocator (std::move (init.allocator))
    {
        init.storage = init.start = init.end = nullptr;
    }

    vector& operator= (vector&& init)                           // Move assignment operator
    {
        if (this == &init)
        {
            return *this;
        }

        bool allocator_move_required = std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value;

        // Move-assignment will replace the allocator only if std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value is true
        if (allocator != init.allocator &&  allocator_move_required == false)
        {
            for (size_t i = 0; i < end - start; i++)
            {
                // Деконструирует объекты типа NypeValue на занятой памяти, вызывая allocator.destroy,
                // если не получается, то (start + i)->~TypeValue
                std::allocator_traits<Allocator>::destroy (allocator, start + i);
            }

            if (storage - start < init.storage - init.start)
            {
                std::allocator_traits<Allocator>::deallocate (allocator, start, storage - start);
                start   = std::allocator_traits<Allocator>::allocate (allocator, init.storage - init.start);
                storage = start + (init.storage - init.start);
            }

            end = start + (init.end - init.start);
            for (size_t i = 0; i < end - start; i++)
            {
                std::allocator_traits<Allocator>::construct (allocator, start + i, *(init.start + i) );
            }

            init.destruct ();
        }
        else
        {
            destruct ();

            if (allocator_move_required == true)
            {
                allocator = std::move (init.allocator);
            }

            start   = init.start;
            storage = init.storage;
            end     = init.end;

            init.storage = init.start = init.end = nullptr;
        }

        return *this;
    }


    TypeValue& at (size_t index)
    {
        if (index > end - start)
            throw std::out_of_range("index > number of elemnts in vector");

        return *(start + index);
    }

    const TypeValue& at (size_t index) const
    {
        if (index > end - start)
            throw std::out_of_range("index > number of elemnts in vector");

        return *(start + index);
    }

    TypeValue& operator[] (size_t index)
    { return *(start + index); }

    const TypeValue& operator[] (size_t index) const
    { return *(start + index); }

    TypeValue& front ()
    { return *start; }

    const TypeValue& front () const
    { return *start; }

    TypeValue& back ()
    { return *(end - 1); }

    const TypeValue& back () const
    { return *(end - 1); }

    constexpr TypeValue* data () noexcept
    { return start; }

    constexpr const TypeValue* data () const noexcept
    { return start; }

    bool empty () const
    { return start == end - 1; }

    size_t size () const
    { return end - start - 1; }

    size_t capacity () const
    { return storage - start; }

private:
    template<typename... Arguments>
    void realloc_insert (Arguments&&... arguments)
    {
        size_t new_size      = 2*(storage - start);
        TypeValue* new_start = std::allocator_traits<Allocator>::allocate (allocator, new_size);

        std::allocator_traits<Allocator>::construct (allocator, new_start + (end - start - 1), std::forward<Arguments> (arguments)... );

        for (size_t i = 0; i < end - start - 1; i++)
        {
            std::allocator_traits<Allocator>::construct (allocator, new_start + i, *(start + i) );
        }

        // Замечание: так как мы перемещаем, если мы будет push_back'ать
        // элемент самого вектора (ну вдруг, типа push_back(v.front()), то
        // если бы мы клали value в конце, то к тому моменту он был бы невалиден
        // (Мы его переместили, а потом захотели положить в конец)

        destruct ();

        start   = new_start;
        end     = start + new_size / 2 + 1;
        storage = start + new_size;
    }

public:

    void push_back (const TypeValue& init)
    {
        if (end == storage)
        {
            realloc_insert (init);
            return;
        }

        std::allocator_traits<Allocator>::construct (allocator, end - 1, init);
        end++;
    }

    template<typename... Arguments>
    TypeValue& emplace_back (Arguments... arguments)
    {
        if (end == storage)
        {
            realloc_insert (std::forward<Arguments> (arguments)... );

        }
        else
        {
            std::allocator_traits<Allocator>::construct (allocator, end - 1, std::forward<Arguments> (arguments)...);
            end++;
        }

        return back ();
    }

    void push_back (TypeValue&& init)
    {
        if (end == storage)
        {
            realloc_insert (std::move_if_noexcept (init) );
            return;
        }

        std::allocator_traits<Allocator>::construct (allocator, end - 1, init);
        end++;
    }

    void pop_back ()
    { std::allocator_traits<Allocator>::destroy (--end - 1); };

    void dump ()
    {
        std::cout << "Size     = " << size () << "\n";
        std::cout << "Capacity = " << capacity () << "\n";
        std::cout << "Empty    = " << empty () << "\n";
        for (TypeValue* i = start; i < end - 1; i++)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }

};




#endif // MY_VEC
