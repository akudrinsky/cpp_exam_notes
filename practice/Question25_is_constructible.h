#include <iostream>
#include <type_traits>

struct S {
    S (int) {
        
    }
    
    S () {
        
    }
};

// Bad version that requires args to have default constructor
// template <typename T, typename... args>
// struct is_constructible {
// private:
//     template <typename T_, typename... args_>
//     static int f (...) {
//         return 0;
//     }
    
//     template <typename T_, typename... args_>
//     static decltype (T_ (args_()...), char ()) f (int x) {
//         return 0;
//     }
// public:
//     static const bool value = std::is_same<decltype (f<T, args...> (0)), char>::value;
// };

// Better version that takes advantage of std::declval usage.

template<typename T, typename U>
struct is_same {
    static const bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static const bool value = true;
};

template<typename T, typename... Args>
struct is_constructible {
private:
    static void detect(...);

    template<typename U>
    static decltype(U(std::declval<Args>()...)) detect(const U&);

public:
    static const bool value = is_same<decltype(detect(std::declval<T>())), T>::value;
};

int main () {
    std::cout << is_constructible<S, int>::value << is_constructible<S, int, int>::value;
}
