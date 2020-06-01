#ifndef UNTITLED1_INSERTER_H
#define UNTITLED1_INSERTER_H

template<typename Container>
struct insert_iterator
{
    Container&                   val;
    typename Container::iterator it;

    insert_iterator (Container& init, typename Container::iterator it):
        val(init),
        it (it)
    { }

    insert_iterator& operator++ ()    { return *this; }
    insert_iterator& operator++ (int) { return *this; }
    insert_iterator& operator*  ()    { return *this; }

    insert_iterator& operator=  (const typename Container::value_type& value)
    {
        it = val->insert(it, value);
        ++it;
        return *this;
    }

    insert_iterator& operator=  (typename Container::value_type&& value)
    {
        iter = container->insert(iter, std::move(value));
        ++iter;
        return *this;
    }
};

template<typename Container>
inline insert_iterator<Container, typename Container::iterator>
       inserter (Container& val, Container::iterator it)
{
    return insert_iterator<Container>(val, it);
}




#endif //UNTITLED1_INSERTER_H
