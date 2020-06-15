#include <iostream>
#include <type_traits>

struct S {
    S (int) {
        
    }
    
    S () {
        
    }
};

template <typename T, typename... args>
struct is_constructible {
private:
    template <typename T_, typename... args_>
    static int f (...) {
        return 0;
    }
    
    template <typename T_, typename... args_>
    static decltype (T_ (args_()...), char ()) f (int x) {
        return 0;
    }
public:
    static const bool value = std::is_same<decltype (f<T, args...> (0)), char>::value;
};

int main () {
    std::cout << is_constructible<S, int>::value << is_constructible<S, int, int>::value;
}
