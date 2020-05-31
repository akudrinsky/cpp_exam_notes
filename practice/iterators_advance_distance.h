#ifndef UNTITLED1_ITERATORS_ADVANCE_DISTANCE_H
#define UNTITLED1_ITERATORS_ADVANCE_DISTANCE_H


#include <cstdlib>
#include <type_traits>
#include <iterator>


// Variant 1
template<typename Iterator, bool expr>
struct advance_help1
{
    constexpr static void advance_impl (Iterator& it, int n) {
        it += n;
    }
};

template<typename Iterator>
struct advance_help1<Iterator, false>
{
    constexpr static void advance_impl (Iterator& it, int n)
    {
        for (size_t i = 0; i < n; i++)
            ++it;
    }
};

template<typename Iterator>
constexpr void advance1 (Iterator& it, int n)
{
    advance_help1<Iterator, std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value>::advance_impl (it, n);
}



template<typename Iterator, bool expr>
struct distance_help1
{
    constexpr static size_t distance_impl (Iterator it1, Iterator it2)
    {
        return it2 - it1;
    }
};

template<typename Iterator>
struct distance_help1<Iterator, false>
{
    constexpr static size_t distance_impl (Iterator it1, Iterator it2)
    {
        size_t ans = 0;
        for (auto i = it1; it1 != it2; ++it1)
            ans++;

        return ans;
    }
};

template<typename Iterator>
constexpr size_t my_distance1 (Iterator it1, Iterator it2)
{
    return distance_help1<Iterator, std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value>::distance_impl (it1, it2);
}
//

// Variant 2
template<typename Iterator>
void advance_impl (Iterator& it, int n, std::random_access_iterator_tag)
{
    it += n;
}


template<typename Iterator>
void advance_impl (Iterator& it, int n, std::bidirectional_iterator_tag)
{
    for (size_t i = 0; i < n; i++)
        ++it;
}


template<typename Iterator>
void advance (Iterator& it, int n)
{
    advance_impl (it, n, typename std::iterator_traits<Iterator>::iterator_category ());
}


template<typename Iterator>
size_t distance_impl (Iterator it1, Iterator it2, std::random_access_iterator_tag)
{
    return it2 - it1;
}


template<typename Iterator>
size_t distance_impl (Iterator it1, Iterator it2, std::input_iterator_tag)
{
    size_t ans = 0;
    for (auto i = it1; it1 != it2; ++it1)
        ans++;

    return ans;
}

template<typename Iterator>
size_t my_distance (Iterator it1, Iterator it2)
{
    return distance_impl (it1, it2, typename std::iterator_traits<Iterator>::iterator_category());
}
//

#endif //UNTITLED1_ITERATORS_ADVANCE_DISTANCE_H
