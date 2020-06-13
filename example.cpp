#include <iostream>

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

int main() {
    int x;
    
    move (x);
    
    return 0;
}
