#ifndef UNTITLED1_IS_CONSTRUCTIBLE_H
#define UNTITLED1_IS_CONSTRUCTIBLE_H

template<typename TypeValue, typename... Arguments>
class is_method
{
private:

    template<typename...>
    static char test (...)
    { return 0; }

    template<typename FuncTypeValue, typename... FuncArguments>
    static decltype (std::declval<FuncTypeValue>().test_method /* here write name of method */
            (std::declval<FuncArguments>()...), int() ) test (int val)        // declval ?
    { return 0; }


public:
    static const bool value = std::is_same<decltype (test<TypeValue, Arguments...> (0)), int>::value;
};




template<typename TypeValue, typename... Arguments>
class is_constructible
{
private:

    template<typename...>
    static char test (...)
    { return 0; }

    template<typename FuncTypeValue, typename... FuncArguments>
    static decltype (FuncTypeValue (std::declval<FuncArguments>()...), int() ) test (int val)
    { return 0; }


public:
    static const bool value = std::is_same<decltype (test<TypeValue, Arguments...> (0)), int>::value;
};

#endif //UNTITLED1_IS_CONSTRUCTIBLE_H
