#include <iostream>
#include <utility>

template <typename T>
struct remove_ref       { typedef T type; };

template <typename T>
struct remove_ref<T&>   { typedef T type; };

template <typename T>
struct remove_ref<T&&>  { typedef T type; };

template <typename T>
typename remove_ref<T>::type&& move (T&& obj) {
    return obj;
}

#include <iostream>
#include <utility>

void f (int& a) {
    std::cout << "lvalue " << a << '\n';
}

int main() {
    int x = 0;
    
    f (0);
    f (x);
    
    return 0;
}
