#ifndef UNTITLED1_NORMAL_ITERATOR_RANDOM_ACCESS_H
#define UNTITLED1_NORMAL_ITERATOR_RANDOM_ACCESS_H

/* Это RandomAccessIterator, в классе достаточно указать поля begin/end, etc...
 * Пример вектора:
 *   normal_iterator<TypeValue> begin ()
 *   { return normal_iterator (start); }
 *
*    const normal_iterator<TypeValue> begin () const
 *   { return normal_iterator (start); }
 *
 *   normal_iterator<TypeValue> end ()
 *   { return normal_iterator (end_ - 1); }
 *
 *   const normal_iterator<TypeValue> end () const
 *   { return normal_iterator (end_ - 1); }
 *
 *
 * Проверялось на цикле foreach и std::copy в поток вывода
 *
*/


/* В файле встречаются выкладки из "stl_iterators.h", одна из них, и самая
 * на мой взгляд разная, что для (вроде)всех функций вне структуры
 * нужны две версии, одна с одним типом итераторов, другая с двумя.
 * (строка 102) сразу после класса
*/


template<typename TypeValue>
class normal_iterator
{
private:

    TypeValue* iterator;

    using it_traits = std::iterator_traits<TypeValue*>;
public:

//  needs for some functions work
    typedef typename it_traits::iterator_category iterator_category;
    typedef typename it_traits::value_type  	  value_type;
    typedef typename it_traits::difference_type   difference_type;
    typedef typename it_traits::reference 	      reference;
    typedef typename it_traits::pointer   	      pointer;
//
    
    
    explicit normal_iterator (TypeValue* init):
            iterator (init)
    { }



    // Forward iterator requirements
    TypeValue& operator*() const noexcept
    { return *iterator; }

    TypeValue* operator->() const noexcept
    { return iterator; }

    normal_iterator& operator++() noexcept
    {
        ++iterator;
        return *this;
    }

    normal_iterator operator++(int) noexcept
    { return normal_iterator(iterator++); }

    // Bidirectional iterator requirements
    normal_iterator& operator--() noexcept
    {
        --iterator;
        return *this;
    }

    normal_iterator operator--(int) noexcept
    { return __normal_iterator(iterator--); }

    // Random access iterator requirements
    TypeValue& operator[](int index) const noexcept
    { return iterator[index]; }

    normal_iterator& operator+=(int index) noexcept
    {
        iterator += index;
        return *this;
    }

    normal_iterator operator+(int plus) const noexcept
    { return normal_iterator (iterator + plus); }

    normal_iterator& operator-=(int sub) noexcept
    {
        iterator -= sub;
        return *this;
    }

    normal_iterator operator-(int sub) const noexcept
    { return __normal_iterator (iterator - sub); }

    const TypeValue* base() const noexcept
    { return iterator; }
};

// Note: In what follows, the left- and right-hand-side iterators are
// allowed to vary in types (conceptually in cv-qualification) so that
// comparison between cv-qualified and non-cv-qualified iterators be
// valid.  However, the greedy and unfriend_ly operators in std::rel_ops
// will make overload resolution ambiguous (when in scope) if we don't
// provide overloads whose operands are of the same type.  Can someone
// remind me what generic programming is about? -- Gaby

// Forward iterator requirements
template<typename TypeValue>
inline bool operator== (const normal_iterator<TypeValue>& lhs,
                        const normal_iterator<TypeValue>& rhs) noexcept
{ return rhs.base() == rhs.base(); }

template<typename TypeValue>
inline bool operator!= (const normal_iterator<TypeValue>& lhs,
                        const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() != rhs.base(); }

// Random access iterator requirements
template<typename TypeValue>
inline bool operator< (const normal_iterator<TypeValue>& lhs,
                       const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() < rhs.base(); }


template<typename TypeValue>
inline bool operator> (const normal_iterator<TypeValue>& lhs,
                       const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() > rhs.base(); }

template<typename TypeValue>
inline bool operator<= (const normal_iterator<TypeValue>& lhs,
                        const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() <= rhs.base(); }


template<typename TypeValue>
inline bool operator>= (const normal_iterator<TypeValue>& lhs,
                        const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() >= rhs.base(); }

// _GLIBCXX_RESOLVE_LIB_DEFECTS
// According to the resolution of DR179 not only the various comparison
// operators but also operator- must accept mixed iterator/const_iterator
// parameters.

template<typename TypeValue>
inline int operator- (const normal_iterator<TypeValue>& lhs,
                      const normal_iterator<TypeValue>& rhs) noexcept
{ return lhs.base() - rhs.base(); }

template<typename TypeValue>
inline normal_iterator<TypeValue>
operator+ (int plus, const normal_iterator<TypeValue>& rhs) noexcept
{ return normal_iterator<TypeValue>(rhs.base () + plus); }

template<typename TypeValue>
inline normal_iterator<TypeValue>
operator- (int sub, const normal_iterator<TypeValue>& rhs) noexcept
{ return normal_iterator<TypeValue>(rhs.base () - sub); }


#endif //UNTITLED1_NORMAL_ITERATOR_RANDOM_ACCESS_H
