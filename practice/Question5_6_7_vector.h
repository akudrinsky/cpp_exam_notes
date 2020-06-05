#ifndef MY_VEC
#define MY_VEC


#include <stdexcept>
#include <utility>
#include <bitset>
#include "normal_iterator(random_access).h"

template<typename TypeValue>
class normal_iterator;

template<typename TypeValue, typename Allocator = std::allocator<TypeValue>>
class vector
{
private:

    TypeValue* start;
    TypeValue* end_;
    TypeValue* storage;
    Allocator  allocator;

    enum vector_const {
        BASE_SIZE = 8,
    };

public:

    vector (const Allocator& alloc = Allocator() ):
            start     (std::allocator_traits<Allocator>::allocate (allocator, BASE_SIZE) ),
            end_       (start + 1),
            storage   (start + BASE_SIZE),
            allocator (alloc)
    { };

    // Rule of five

    // Rule of three
    vector (const vector& init):                                // Copy constructor
            start     (std::allocator_traits<Allocator>::allocate (allocator, init.storage - init.start)),  // Аллоцирует (init.storage - init.start) * sizeof(TypeValue) байт памяти
            end_       (start + (init.end_ - init.start) ),
            storage   (start + (init.storage - init.start)),
            allocator (std::allocator_traits<Allocator>::select_on_container_copy_construction (init.allocator))
    // Copy constructors of AllocatorAwareContainers obtain their instances of the allocator
    // by calling std::allocator_traits<allocator_type>::select_on_container_copy_construction on the allocator of the container being copied.
    {
        for (size_t i = 0; i < init.end_ - init.start; i++)
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

        for (size_t i = 0; i < end_ - start; i++)
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
            start   = std::allocator_traits<Allocator>::allocate (allocator, init.end_ - init.start);
            storage = start + (init.end_ - init.start);
        }

        end_ = start + (init.end_ - init.start);



        for (size_t i = 0; i < init.end_ - init.start; i++)
        {
            // Конструирует объекты типа TypeValue на выделенной памяти
            std::allocator_traits<Allocator>::construct (allocator, start + i, *(init.start + i));
        }

        return *this;
    }

    void destruct ()
    {
        for (size_t i = 0; i < end_ - start; i++)
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
            end_       (init.end_),
            storage   (init.storage),
            allocator (std::move (init.allocator))
    {
        init.storage = init.start = init.end_ = nullptr;
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
            for (size_t i = 0; i < end_ - start; i++)
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

            end_ = start + (init.end_ - init.start);
            for (size_t i = 0; i < end_ - start; i++)
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
            end_     = init.end_;

            init.storage = init.start = init.end_ = nullptr;
        }

        return *this;
    }


    TypeValue& at (size_t index)
    {
        if (index > end_ - start)
            throw std::out_of_range("index > number of elemnts in vector");

        return *(start + index);
    }

    const TypeValue& at (size_t index) const
    {
        if (index > end_ - start)
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
    { return *(end_ - 1); }

    const TypeValue& back () const
    { return *(end_ - 1); }

    constexpr TypeValue* data () noexcept
    { return start; }

    constexpr const TypeValue* data () const noexcept
    { return start; }

    bool empty () const
    { return start == end_ - 1; }

    size_t size () const
    { return end_ - start - 1; }

    size_t capacity () const
    { return storage - start; }

private:
    template<typename... Arguments>
    void realloc_insert (Arguments&&... arguments)
    {
        size_t new_size      = 2*(storage - start);
        TypeValue* new_start = std::allocator_traits<Allocator>::allocate (allocator, new_size);

        std::allocator_traits<Allocator>::construct (allocator, new_start + (end_ - start - 1), std::forward<Arguments> (arguments)... );

        for (size_t i = 0; i < end_ - start - 1; i++)
        {
            std::allocator_traits<Allocator>::construct (allocator, new_start + i, *(start + i) );
        }

        // Замечание: так как мы перемещаем, если мы будет push_back'ать
        // элемент самого вектора (ну вдруг, типа push_back(v.front()), то
        // если бы мы клали value в конце, то к тому моменту он был бы невалиден
        // (Мы его переместили, а потом захотели положить в конец)

        destruct ();

        start   = new_start;
        end_     = start + new_size / 2 + 1;
        storage = start + new_size;
    }

public:

    void push_back (const TypeValue& init)
    {
        if (end_ == storage)
        {
            realloc_insert (init);
            return;
        }

        std::allocator_traits<Allocator>::construct (allocator, end_ - 1, init);
        end_++;
    }

    template<typename... Arguments>
    TypeValue& emplace_back (Arguments... arguments)
    {
        if (end_ == storage)
        {
            realloc_insert (std::forward<Arguments> (arguments)... );

        }
        else
        {
            std::allocator_traits<Allocator>::construct (allocator, end_ - 1, std::forward<Arguments> (arguments)...);
            end_++;
        }

        return back ();
    }

    void push_back (TypeValue&& init)
    {
        if (end_ == storage)
        {
            realloc_insert (std::move_if_noexcept (init) );
            return;
        }

        std::allocator_traits<Allocator>::construct (allocator, end_ - 1, init);
        end_++;
    }

    void pop_back ()
    { std::allocator_traits<Allocator>::destroy (--end_ - 1); };

    void dump ()
    {
        std::cout << "Size     = " << size () << "\n";
        std::cout << "Capacity = " << capacity () << "\n";
        std::cout << "Empty    = " << empty () << "\n";
        for (TypeValue* i = start; i < end_ - 1; i++)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }


    normal_iterator<TypeValue> begin ()
    { return normal_iterator (start); }

    const normal_iterator<TypeValue> begin () const
    { return normal_iterator (start); }

    normal_iterator<TypeValue> end ()
    { return normal_iterator (end_ - 1); }

    const normal_iterator<TypeValue> end () const
    { return normal_iterator (end_ - 1); }

};


template<>
class vector<bool>
{
private:
    using proxy_type = unsigned long;

    proxy_type* start;
    size_t      elements;
    size_t      storage;

    struct BoolProxy
    {
        proxy_type* cur_pointer;
        size_t      cur_elem;

        BoolProxy () = delete;
        explicit BoolProxy (proxy_type* init_pointer, size_t init_elem):
            cur_pointer (init_pointer),
            cur_elem    (init_elem)
        { }

        bool bit ()
        { return (*cur_pointer >> cur_elem) & 0x1; }

        static void set_bit (proxy_type* cur_pointer, size_t cur_elem, bool condition)
        {
            if (condition == true)
            {
                (*cur_pointer) |= (0x01 << cur_elem);
            }
            else
            {
                (*cur_pointer) &= ~(0x01 << cur_elem);
            }
        }

        void set_bit (bool condition)
        { set_bit (cur_pointer, cur_elem, condition); }

        BoolProxy& operator= (bool init)
        {
            set_bit (init);
            return *this;
        }

        operator bool ()
        { return bit (); }
    };

    enum bvector_const {
        BASE_SIZE             = 20,
        SIZE_OF_ARRAY_ELEMENT = sizeof (proxy_type),
    };

public:

    vector ():
        start    (new proxy_type[BASE_SIZE]),    // я хз как тут реализовывать аллокаторы, в стандарте творится поный magic
        elements (0),
        storage  (BASE_SIZE)
    {}


    // Push back реализован только для тестов и отладки
        void push_back (bool init)
        {
        // Тут должна быть проверка на size == capacity, аналогично vectror выше

            BoolProxy::set_bit (start + (elements / SIZE_OF_ARRAY_ELEMENT), elements % SIZE_OF_ARRAY_ELEMENT, init);
            elements++;
        }
    //


    BoolProxy operator[] (size_t index)
    {
        return BoolProxy (start + (index / SIZE_OF_ARRAY_ELEMENT), index % SIZE_OF_ARRAY_ELEMENT);
    }



#include <bitset>
    void dump ()
    {
        std::cout << "size0f(proxy_type) = " << sizeof (proxy_type) << " ELEMENTS     = " << elements << "\n";
        for (size_t i = 0; i < elements / SIZE_OF_ARRAY_ELEMENT +  (elements % SIZE_OF_ARRAY_ELEMENT == 0 ? 0 : 1); i++)
        { std::cout << std::bitset<SIZE_OF_ARRAY_ELEMENT> (*(start + i)) << " "; }
        std::cout << "\n";
    }




};


#endif // MY_VEC
